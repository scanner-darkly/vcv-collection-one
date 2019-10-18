#!/usr/bin/env python3

import sys
import os
import re
import json
import xml.etree.ElementTree


# Version check
f"Python 3.6+ is required"


class UserException(Exception):
    pass


def find(f, array):
    for a in array:
        if f(a):
            return f

def input_default(prompt, default=""):
    str = input(f"{prompt} [{default}]: ")
    if str == "":
        return default
    return str


def is_valid_slug(slug):
    return re.match(r'^[a-zA-Z0-9_\-]+$', slug) != None


def slug_to_identifier(slug):
    if len(slug) == 0 or slug[0].isdigit():
        slug = "_" + slug
    slug = slug[0].upper() + slug[1:]
    slug = slug.replace('-', '_')
    return slug


def create_plugin(slug, plugin_dir=None):
    # Check slug
    if not is_valid_slug(slug):
        raise UserException("Slug must only contain ASCII letters, numbers, '-', and '_'.")

    if not plugin_dir:
        plugin_dir = os.path.join(slug, '')

    # Check if plugin directory exists
    if os.path.exists(plugin_dir):
        raise UserException(f"Directory {plugin_dir} already exists")

    # Create plugin directory
    os.mkdir(plugin_dir)

    # Create manifest
    try:
        create_manifest(slug, plugin_dir)
    except Exception as e:
        os.rmdir(plugin_dir)
        raise e

    # Create subdirectories
    os.mkdir(os.path.join(plugin_dir, "src"))
    os.mkdir(os.path.join(plugin_dir, "res"))

    # Create Makefile
    makefile = """# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
"""
    with open(os.path.join(plugin_dir, "Makefile"), "w") as f:
        f.write(makefile)

    # Create plugin.hpp
    plugin_hpp = """#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin *pluginInstance;

// Declare each Model, defined in each module source file
// extern Model *modelMyModule;
"""
    with open(os.path.join(plugin_dir, "src/plugin.hpp"), "w") as f:
        f.write(plugin_hpp)

    # Create plugin.cpp
    plugin_cpp = """#include "plugin.hpp"


Plugin *pluginInstance;


void init(Plugin *p) {
    pluginInstance = p;

    // Add modules here
    // p->addModel(modelMyModule);

    // Any other plugin initialization may go here.
    // As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
"""
    with open(os.path.join(plugin_dir, "src/plugin.cpp"), "w") as f:
        f.write(plugin_cpp)

    git_ignore = """/build
/dist
/plugin.so
/plugin.dylib
/plugin.dll
.DS_Store
"""
    with open(os.path.join(plugin_dir, ".gitignore"), "w") as f:
        f.write(git_ignore)

    print(f"Created template plugin in {plugin_dir}")
    os.system(f"cd {plugin_dir} && git init")
    print(f"You may use `make`, `make clean`, `make dist`, `make install`, etc in the {plugin_dir} directory.")


def create_manifest(slug, plugin_dir="."):
    # Default manifest
    manifest = {
        'slug': slug,
    }

    # Try to load existing manifest file
    manifest_filename = os.path.join(plugin_dir, 'plugin.json')
    try:
        with open(manifest_filename, "r") as f:
            manifest = json.load(f)
    except:
        pass

    # Query manifest information
    manifest['name'] = input_default("Plugin name", manifest.get('name', slug))
    manifest['version'] = input_default("Version", manifest.get('version', "1.0.0"))
    manifest['license'] = input_default("License (if open-source, use license identifier from https://spdx.org/licenses/)", manifest.get('license', "proprietary"))
    manifest['brand'] = input_default("Brand (prefix for all module names)", manifest.get('brand', manifest['name']))
    manifest['author'] = input_default("Author", manifest.get('author', ""))
    manifest['authorEmail'] = input_default("Author email (optional)", manifest.get('authorEmail', ""))
    manifest['authorUrl'] = input_default("Author website URL (optional)", manifest.get('authorUrl', ""))
    manifest['pluginUrl'] = input_default("Plugin website URL (optional)", manifest.get('pluginUrl', ""))
    manifest['manualUrl'] = input_default("Manual website URL (optional)", manifest.get('manualUrl', ""))
    manifest['sourceUrl'] = input_default("Source code URL (optional)", manifest.get('sourceUrl', ""))
    manifest['donateUrl'] = input_default("Donate URL (optional)", manifest.get('donateUrl', ""))

    if 'modules' not in manifest:
        manifest['modules'] = []

    # Dump JSON
    with open(manifest_filename, "w") as f:
        json.dump(manifest, f, indent="  ")
    print(f"Manifest written to {manifest_filename}")


def create_module(slug, panel_filename=None, source_filename=None):
    # Check slug
    if not is_valid_slug(slug):
        raise UserException("Slug must only contain ASCII letters, numbers, '-', and '_'.")

    # Read manifest
    manifest_filename = 'plugin.json'
    with open(manifest_filename, "r") as f:
        manifest = json.load(f)

    # Check if module manifest exists
    module_manifest = find(lambda m: m['slug'] == slug, manifest['modules'])
    if module_manifest:
        print(f"Module {slug} already exists in plugin.json. Edit this file to modify the module manifest.")

    else:
        # Add module to manifest
        module_manifest = {}
        module_manifest['slug'] = slug
        module_manifest['name'] = input_default("Module name", slug)
        module_manifest['description'] = input_default("One-line description (optional)")
        tags = input_default("Tags (comma-separated, case-insensitive, see https://github.com/VCVRack/Rack/blob/v1/src/plugin.cpp#L511-L571 for list)")
        tags = tags.split(",")
        tags = [tag.strip() for tag in tags]
        if len(tags) == 1 and tags[0] == "":
            tags = []
        module_manifest['tags'] = tags

        manifest['modules'].append(module_manifest)

        # Write manifest
        with open(manifest_filename, "w") as f:
            json.dump(manifest, f, indent="  ")

        print(f"Added {slug} to {manifest_filename}")

    # Check filenames
    if panel_filename and source_filename:
        if not os.path.exists(panel_filename):
            raise UserException(f"Panel not found at {panel_filename}.")

        print(f"Panel found at {panel_filename}. Generating source file.")

        if os.path.exists(source_filename):
            if input_default(f"{source_filename} already exists. Overwrite?", "n").lower() != "y":
                return

        # Read SVG XML
        tree = xml.etree.ElementTree.parse(panel_filename)

        components = panel_to_components(tree)
        print(f"Components extracted from {panel_filename}")

        # Write source
        source = components_to_source(components, slug)

        with open(source_filename, "w") as f:
            f.write(source)
        print(f"Source file generated at {source_filename}")

        # Append model to plugin.hpp
        identifier = slug_to_identifier(slug)

        # Tell user to add model to plugin.hpp and plugin.cpp
        print(f"""
To enable the module, add
extern Model *model{identifier};
to plugin.hpp, and add
p->addModel(model{identifier});
to the init() function in plugin.cpp.""")


def panel_to_components(tree):
    ns = {
        "svg": "http://www.w3.org/2000/svg",
        "inkscape": "http://www.inkscape.org/namespaces/inkscape",
    }

    # Get components layer
    root = tree.getroot()
    groups = root.findall(".//svg:g[@inkscape:label='components']", ns)
    # Illustrator uses `id` for the group name.
    if len(groups) < 1:
        groups = root.findall(".//svg:g[@id='components']", ns)
    if len(groups) < 1:
        raise UserException("Could not find \"components\" layer on panel")

    # Get circles and rects
    components_group = groups[0]
    circles = components_group.findall(".//svg:circle", ns)
    rects = components_group.findall(".//svg:rect", ns)

    components = {}
    components['params'] = []
    components['inputs'] = []
    components['outputs'] = []
    components['lights'] = []
    components['widgets'] = []

    for el in circles + rects:
        c = {}
        # Get name
        name = el.get('{http://www.inkscape.org/namespaces/inkscape}label')
        if name is None:
            name = el.get('id')
        name = slug_to_identifier(name).upper()
        c['name'] = name

        # Get color
        style = el.get('style')
        color_match = re.search(r'fill:\S*#(.{6});', style)
        color = color_match.group(1).lower()
        c['color'] = color

        # Get position
        if el.tag == "{http://www.w3.org/2000/svg}rect":
            x = float(el.get('x'))
            y = float(el.get('y'))
            width = float(el.get('width'))
            height = float(el.get('height'))
            c['x'] = round(x, 3)
            c['y'] = round(y, 3)
            c['width'] = round(width, 3)
            c['height'] = round(height, 3)
            c['cx'] = round(x + width / 2, 3)
            c['cy'] = round(y + height / 2, 3)
        elif el.tag == "{http://www.w3.org/2000/svg}circle":
            cx = float(el.get('cx'))
            cy = float(el.get('cy'))
            c['cx'] = round(cx, 3)
            c['cy'] = round(cy, 3)

        if color == 'ff0000':
            components['params'].append(c)
        if color == '00ff00':
            components['inputs'].append(c)
        if color == '0000ff':
            components['outputs'].append(c)
        if color == 'ff00ff':
            components['lights'].append(c)
        if color == 'ffff00':
            components['widgets'].append(c)

    # Sort components
    top_left_sort = lambda w: (w['cy'], w['cx'])
    components['params'] = sorted(components['params'], key=top_left_sort)
    components['inputs'] = sorted(components['inputs'], key=top_left_sort)
    components['outputs'] = sorted(components['outputs'], key=top_left_sort)
    components['lights'] = sorted(components['lights'], key=top_left_sort)
    components['widgets'] = sorted(components['widgets'], key=top_left_sort)

    print(f"Found {len(components['params'])} params, {len(components['inputs'])} inputs, {len(components['outputs'])} outputs, {len(components['lights'])} lights, and {len(components['widgets'])} custom widgets.")
    return components


def components_to_source(components, slug):
    identifier = slug_to_identifier(slug)
    source = ""

    source += f"""#include "plugin.hpp"


struct {identifier} : Module {{"""

    # Params
    source += """
    enum ParamIds {"""
    for c in components['params']:
        source += f"""
        {c['name']}_PARAM,"""
    source += """
        NUM_PARAMS
    };"""

    # Inputs
    source += """
    enum InputIds {"""
    for c in components['inputs']:
        source += f"""
        {c['name']}_INPUT,"""
    source += """
        NUM_INPUTS
    };"""

    # Outputs
    source += """
    enum OutputIds {"""
    for c in components['outputs']:
        source += f"""
        {c['name']}_OUTPUT,"""
    source += """
        NUM_OUTPUTS
    };"""

    # Lights
    source += """
    enum LightIds {"""
    for c in components['lights']:
        source += f"""
        {c['name']}_LIGHT,"""
    source += """
        NUM_LIGHTS
    };"""


    source += f"""

    {identifier}() {{
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);"""

    for c in components['params']:
        source += f"""
        configParam({c['name']}_PARAM, 0.f, 1.f, 0.f, "");"""

    source += """
    }

    void process(const ProcessArgs &args) override {
    }
};"""

    source += f"""


struct {identifier}Widget : ModuleWidget {{
    {identifier}Widget({identifier} *module) {{
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/{slug}.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));"""


    # Params
    if len(components['params']) > 0:
        source += "\n"
    for c in components['params']:
        if 'x' in c:
            source += f"""
        addParam(createParam<SDScaleSwitch>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_PARAM));"""
        else:
            source += f"""
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_PARAM));"""

    # Inputs
    if len(components['inputs']) > 0:
        source += "\n"
    for c in components['inputs']:
        if 'x' in c:
            source += f"""
        addInput(createInput<SDPort>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_INPUT));"""
        else:
            source += f"""
        addInput(createInputCentered<SDPort>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_INPUT));"""

    # Outputs
    if len(components['outputs']) > 0:
        source += "\n"
    for c in components['outputs']:
        if 'x' in c:
            source += f"""
        addOutput(createOutput<SDPort>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_OUTPUT));"""
        else:
            source += f"""
        addOutput(createOutputCentered<SDPort>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_OUTPUT));"""

    # Lights
    if len(components['lights']) > 0:
        source += "\n"
    for c in components['lights']:
        if 'x' in c:
            source += f"""
        addChild(createLight<MediumLight<SDLight1>>(mm2px(Vec({c['x']}, {c['y']})), module, {identifier}::{c['name']}_LIGHT));"""
        else:
            source += f"""
        addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec({c['cx']}, {c['cy']})), module, {identifier}::{c['name']}_LIGHT));"""

    # Widgets
    if len(components['widgets']) > 0:
        source += "\n"
    for c in components['widgets']:
        if 'x' in c:
            source += f"""
        // mm2px(Vec({c['width']}, {c['height']}))
        addChild(createWidget<Widget>(mm2px(Vec({c['x']}, {c['y']}))));"""
        else:
            source += f"""
        addChild(createWidgetCentered<Widget>(mm2px(Vec({c['cx']}, {c['cy']}))));"""

    source += f"""
    }}
}};


Model *model{identifier} = createModel<{identifier}, {identifier}Widget>("{slug}");"""

    return source


def usage(script):
    text = f"""VCV Rack Plugin Helper Utility

Usage: {script} <command> ...
Commands:

createplugin <slug> [plugin dir]

    A directory will be created and initialized with a minimal plugin template.
    If no plugin directory is given, the slug is used.

createmanifest <slug> [plugin dir]

    Creates a `plugin.json` manifest file in an existing plugin directory.
    If no plugin directory is given, the current directory is used.

createmodule <module slug> [panel file] [source file]

    Adds a new module to the plugin manifest in the current directory.
    If a panel and source file are given, generates a template source file initialized with components from a panel file.
    Example:
        {script} createmodule MyModule res/MyModule.svg src/MyModule.cpp

    See https://vcvrack.com/manual/PanelTutorial.html for creating SVG panel files.
"""
    print(text)


def parse_args(args):
    script = args.pop(0)
    if len(args) == 0:
        usage(script)
        return

    cmd = args.pop(0)
    if cmd == 'createplugin':
        create_plugin(*args)
    elif cmd == 'createmodule':
        create_module(*args)
    elif cmd == 'createmanifest':
        create_manifest(*args)
    else:
        print(f"Command not found: {cmd}")


if __name__ == "__main__":
    try:
        parse_args(sys.argv)
    except KeyboardInterrupt:
        pass
    except UserException as e:
        print(e)
        sys.exit(1)
