#include "plugin.hpp"


struct SDOrcasHeartV2 : Module {
    enum ParamIds {
        SCALE_2_PARAM,
        SCALE_4_PARAM,
        SCALE_7_PARAM,
        SCALE_9_PARAM,
        SCALE_11_PARAM,
        SCALE_PARAM,
        SCALE_A_OCT_PARAM,
        SCALE_A_PARAM,
        SCALE_B_PARAM,
        SCALE_1_PARAM,
        SCALE_3_PARAM,
        SCALE_5_PARAM,
        SCALE_6_PARAM,
        SCALE_8_PARAM,
        SCALE_10_PARAM,
        SCALE_12_PARAM,
        SCALE_14_PARAM,
        SCALE_16_PARAM,
        SCALE_19_PARAM,
        SCALE_21_PARAM,
        SCALE_23_PARAM,
        SCALE_B_OCT_PARAM,
        SCALE_13_PARAM,
        SCALE_15_PARAM,
        SCALE_17_PARAM,
        SCALE_18_PARAM,
        SCALE_20_PARAM,
        SCALE_22_PARAM,
        SCALE_24_PARAM,
        SPEED_PARAM,
        ALGO_X_PARAM,
        SHIFT_PARAM,
        ROTATE_PARAM,
        XMOD_TYPE_PARAM,
        TRANSPOSE_PARAM,
        LENGTH_PARAM,
        ALGO_Y_PARAM,
        SPACE_PARAM,
        SPREAD_PARAM,
        XMOD_PARAM,
        GATE_LEN_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        SCALE_A_OCT_INPUT,
        SCALE_A_INPUT,
        SCALE_INPUT,
        SCALE_B_OCT_INPUT,
        SCALE_B_INPUT,
        CLOCK_INPUT,
        RESET_INPUT,
        SPEED_INPUT,
        LENGTH_INPUT,
        ALGO_X_INPUT,
        ALGO_Y_INPUT,
        SHIFT_INPUT,
        SPACE_INPUT,
        ROTATE_INPUT,
        SPREAD_INPUT,
        XMOD_TYPE_INPUT,
        XMOD_INPUT,
        TRANSPOSE_INPUT,
        GATE_LEN_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        CLOCK_OUTPUT,
        MOD_CV_1_OUTPUT,
        MOD_CV_2_OUTPUT,
        MOD_CV_3_OUTPUT,
        MOD_CV_4_OUTPUT,
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        CV_5_OUTPUT,
        CV_6_OUTPUT,
        CV_7_OUTPUT,
        CV_8_OUTPUT,
        MOD_GATE_1_OUTPUT,
        MOD_GATE_2_OUTPUT,
        MOD_GATE_3_OUTPUT,
        MOD_GATE_4_OUTPUT,
        GATE_1_OUTPUT,
        GATE_2_OUTPUT,
        GATE_3_OUTPUT,
        GATE_4_OUTPUT,
        GATE_5_OUTPUT,
        GATE_6_OUTPUT,
        GATE_7_OUTPUT,
        GATE_8_OUTPUT,
        RESET_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        SCALE_A_LIGHT,
        SCALE_A_LIGHT,
        NUM_LIGHTS
    };

    SDOrcasHeartV2() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(SCALE_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_9_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_11_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_A_OCT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_A_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_B_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_10_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_12_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_14_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_16_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_19_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_21_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_23_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_B_OCT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_13_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_15_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_17_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_18_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_20_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_22_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SCALE_24_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPEED_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ALGO_X_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SHIFT_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ROTATE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(XMOD_TYPE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(TRANSPOSE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LENGTH_PARAM, 0.f, 1.f, 0.f, "");
        configParam(ALGO_Y_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPACE_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SPREAD_PARAM, 0.f, 1.f, 0.f, "");
        configParam(XMOD_PARAM, 0.f, 1.f, 0.f, "");
        configParam(GATE_LEN_PARAM, 0.f, 1.f, 0.f, "");
    }

    void process(const ProcessArgs &args) override {
    }
};


struct SDOrcasHeartV2Widget : ModuleWidget {
    SDOrcasHeartV2Widget(SDOrcasHeartV2 *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeartV2.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(52.661, 12.386)), module, SDOrcasHeartV2::SCALE_2_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(61.615, 12.386)), module, SDOrcasHeartV2::SCALE_4_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(79.522, 12.386)), module, SDOrcasHeartV2::SCALE_7_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(88.476, 12.386)), module, SDOrcasHeartV2::SCALE_9_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(97.429, 12.386)), module, SDOrcasHeartV2::SCALE_11_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(28.817, 14.481)), module, SDOrcasHeartV2::SCALE_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(113.681, 14.481)), module, SDOrcasHeartV2::SCALE_A_OCT_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(10.77, 14.492)), module, SDOrcasHeartV2::SCALE_A_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(141.63, 14.495)), module, SDOrcasHeartV2::SCALE_B_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(48.184, 17.106)), module, SDOrcasHeartV2::SCALE_1_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(57.138, 17.106)), module, SDOrcasHeartV2::SCALE_3_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(66.092, 17.106)), module, SDOrcasHeartV2::SCALE_5_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(75.045, 17.106)), module, SDOrcasHeartV2::SCALE_6_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(83.999, 17.106)), module, SDOrcasHeartV2::SCALE_8_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(92.953, 17.106)), module, SDOrcasHeartV2::SCALE_10_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(101.906, 17.106)), module, SDOrcasHeartV2::SCALE_12_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(52.132, 28.169)), module, SDOrcasHeartV2::SCALE_14_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(61.086, 28.169)), module, SDOrcasHeartV2::SCALE_16_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(78.993, 28.169)), module, SDOrcasHeartV2::SCALE_19_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(87.947, 28.169)), module, SDOrcasHeartV2::SCALE_21_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(96.9, 28.169)), module, SDOrcasHeartV2::SCALE_23_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(113.681, 30.264)), module, SDOrcasHeartV2::SCALE_B_OCT_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(47.655, 32.889)), module, SDOrcasHeartV2::SCALE_13_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(56.609, 32.889)), module, SDOrcasHeartV2::SCALE_15_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(65.562, 32.889)), module, SDOrcasHeartV2::SCALE_17_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(74.516, 32.889)), module, SDOrcasHeartV2::SCALE_18_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(83.47, 32.889)), module, SDOrcasHeartV2::SCALE_20_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(92.423, 32.889)), module, SDOrcasHeartV2::SCALE_22_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(101.377, 32.889)), module, SDOrcasHeartV2::SCALE_24_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(20.284, 50.164)), module, SDOrcasHeartV2::SPEED_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(42.651, 50.164)), module, SDOrcasHeartV2::ALGO_X_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(65.017, 50.164)), module, SDOrcasHeartV2::SHIFT_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(87.383, 50.164)), module, SDOrcasHeartV2::ROTATE_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(109.749, 50.164)), module, SDOrcasHeartV2::XMOD_TYPE_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(132.115, 50.164)), module, SDOrcasHeartV2::TRANSPOSE_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(31.468, 67.91)), module, SDOrcasHeartV2::LENGTH_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(53.834, 67.91)), module, SDOrcasHeartV2::ALGO_Y_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(76.2, 67.91)), module, SDOrcasHeartV2::SPACE_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(98.566, 67.91)), module, SDOrcasHeartV2::SPREAD_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(120.932, 67.91)), module, SDOrcasHeartV2::XMOD_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(143.299, 67.91)), module, SDOrcasHeartV2::GATE_LEN_PARAM));

        addInput(createInputCentered<SDPort>(mm2px(Vec(124.776, 14.481)), module, SDOrcasHeartV2::SCALE_A_OCT_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(10.77, 30.264)), module, SDOrcasHeartV2::SCALE_A_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(28.817, 30.264)), module, SDOrcasHeartV2::SCALE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(124.776, 30.264)), module, SDOrcasHeartV2::SCALE_B_OCT_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(141.63, 30.264)), module, SDOrcasHeartV2::SCALE_B_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(9.101, 67.91)), module, SDOrcasHeartV2::CLOCK_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(9.101, 82.004)), module, SDOrcasHeartV2::RESET_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(20.284, 82.004)), module, SDOrcasHeartV2::SPEED_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(31.468, 82.004)), module, SDOrcasHeartV2::LENGTH_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(42.651, 82.004)), module, SDOrcasHeartV2::ALGO_X_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(53.834, 82.004)), module, SDOrcasHeartV2::ALGO_Y_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(65.017, 82.004)), module, SDOrcasHeartV2::SHIFT_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(76.2, 82.004)), module, SDOrcasHeartV2::SPACE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(87.383, 82.004)), module, SDOrcasHeartV2::ROTATE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(98.566, 82.004)), module, SDOrcasHeartV2::SPREAD_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(109.749, 82.004)), module, SDOrcasHeartV2::XMOD_TYPE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(120.932, 82.004)), module, SDOrcasHeartV2::XMOD_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(132.115, 82.004)), module, SDOrcasHeartV2::TRANSPOSE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(143.299, 82.004)), module, SDOrcasHeartV2::GATE_LEN_INPUT));

        addOutput(createOutputCentered<SDPort>(mm2px(Vec(9.101, 103.371)), module, SDOrcasHeartV2::CLOCK_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(20.284, 103.371)), module, SDOrcasHeartV2::MOD_CV_1_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(31.468, 103.371)), module, SDOrcasHeartV2::MOD_CV_2_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(42.651, 103.371)), module, SDOrcasHeartV2::MOD_CV_3_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(53.834, 103.371)), module, SDOrcasHeartV2::MOD_CV_4_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(65.017, 103.371)), module, SDOrcasHeartV2::CV_1_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(76.2, 103.371)), module, SDOrcasHeartV2::CV_2_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(87.383, 103.371)), module, SDOrcasHeartV2::CV_3_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(98.566, 103.371)), module, SDOrcasHeartV2::CV_4_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(109.749, 103.371)), module, SDOrcasHeartV2::CV_5_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(120.932, 103.371)), module, SDOrcasHeartV2::CV_6_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(132.116, 103.371)), module, SDOrcasHeartV2::CV_7_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(143.299, 103.371)), module, SDOrcasHeartV2::CV_8_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(20.284, 119.154)), module, SDOrcasHeartV2::MOD_GATE_1_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(31.468, 119.154)), module, SDOrcasHeartV2::MOD_GATE_2_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(42.651, 119.154)), module, SDOrcasHeartV2::MOD_GATE_3_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(53.834, 119.154)), module, SDOrcasHeartV2::MOD_GATE_4_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(65.017, 119.154)), module, SDOrcasHeartV2::GATE_1_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(76.2, 119.154)), module, SDOrcasHeartV2::GATE_2_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(87.383, 119.154)), module, SDOrcasHeartV2::GATE_3_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(98.566, 119.154)), module, SDOrcasHeartV2::GATE_4_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(109.749, 119.154)), module, SDOrcasHeartV2::GATE_5_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(120.932, 119.154)), module, SDOrcasHeartV2::GATE_6_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(132.115, 119.154)), module, SDOrcasHeartV2::GATE_7_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(143.299, 119.154)), module, SDOrcasHeartV2::GATE_8_OUTPUT));
        addOutput(createOutputCentered<SDPort>(mm2px(Vec(9.101, 119.155)), module, SDOrcasHeartV2::RESET_OUTPUT));

        addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(41.298, 14.481)), module, SDOrcasHeartV2::SCALE_A_LIGHT));
        addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(41.298, 30.264)), module, SDOrcasHeartV2::SCALE_A_LIGHT));
    }
};


Model *modelSDOrcasHeartV2 = createModel<SDOrcasHeartV2, SDOrcasHeartV2Widget>("SDOrcasHeartV2");