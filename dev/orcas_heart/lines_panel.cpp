#include "plugin.hpp"


struct Lines : Module {
    enum ParamIds {
        NUM_PARAMS
    };
    enum InputIds {
        IN_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        NUM_OUTPUTS
    };
    enum LightIds {
        NUM_LIGHTS
    };

    Lines() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    }

    void process(const ProcessArgs &args) override {
    }
};


struct LinesWidget : ModuleWidget {
    LinesWidget(Lines *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Lines.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addInput(createInputCentered<SDPort>(mm2px(Vec(5.08, 119.155)), module, Lines::IN_INPUT));

        // mm2px(Vec(10.16, 100.181))
        addChild(createWidget<Widget>(mm2px(Vec(0.0, 10.463))));
    }
};


Model *modelLines = createModel<Lines, LinesWidget>("Lines");