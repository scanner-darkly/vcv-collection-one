#include "plugin.hpp"
#include "SharedComponents.hpp"

struct SDLines : Module {
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

    SDLines() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    }

    void process(const ProcessArgs &args) override {
    }
};


struct SDLinesWidget : ModuleWidget {
    SDLinesWidget(SDLines *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDLines.svg")));

        addInput(createInputCentered<SDPort>(mm2px(Vec(5.08, 119.155)), module, SDLines::IN_INPUT));
    }
};


Model *modelSDLines = createModel<SDLines, SDLinesWidget>("Lines");