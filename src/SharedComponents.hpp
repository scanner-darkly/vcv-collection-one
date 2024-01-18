#pragma once
#include <rack.hpp>

struct SDPort : app::SvgPort {
    SDPort() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_port.svg")));
    }
};

struct SDLargeKnob : app::SvgKnob {
    SDLargeKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_knob3.svg")));
    }
};

struct SDMediumKnob : app::SvgKnob {
    SDMediumKnob() {
        minAngle = -0.83 * M_PI;
        maxAngle = 0.83 * M_PI;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_knob_med.svg")));
    }
};

struct SDScaleSwitch : app::SvgSwitch {
    SDScaleSwitch() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_scale_off_1.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_scale_on_1.svg")));
    }
};

struct SDButton : app::SvgSwitch {
    SDButton() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_button2.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_button1.svg")));
    }
};

struct SDMomentaryButton : app::SvgSwitch {
    SDMomentaryButton() {
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_button2.svg")));
        addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/sd_button1.svg")));
        momentary = true;
    }
};

struct SDLight1 : GrayModuleLightWidget {
	SDLight1() {
		addBaseColor(nvgRGB(0xf0, 0xf5, 0xff));
	}
};
