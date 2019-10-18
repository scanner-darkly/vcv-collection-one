#include "plugin.hpp"


struct SDOrcasHeart : Module {
	enum ParamIds {
		LENGTH_PARAM,
		TRANSPOSE_PARAM,
		ALGO_X_PARAM,
		SHIFT_PARAM,
		SPEED_PARAM,
		GATE_LEN_PARAM,
		ALGO_Y_PARAM,
		SPACE_PARAM,
		SCALE_2_PARAM,
		SCALE_4_PARAM,
		SCALE_7_PARAM,
		SCALE_9_PARAM,
		SCALE_11_PARAM,
		SCALE_A_PARAM,
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
		SCALE_PARAM,
		SCALE_B_PARAM,
		SCALE_13_PARAM,
		SCALE_15_PARAM,
		SCALE_17_PARAM,
		SCALE_18_PARAM,
		SCALE_20_PARAM,
		SCALE_22_PARAM,
		SCALE_24_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		EXP_1_INPUT,
		EXP_2_INPUT,
		SCALE_A_INPUT,
		RESET_INPUT,
		SCALE_INPUT,
		SCALE_B_INPUT,
		LENGTH_INPUT,
		ALGO_X_INPUT,
		SHIFT_INPUT,
		TRANSPOSE_INPUT,
		SPEED_INPUT,
		ALGO_Y_INPUT,
		SPACE_INPUT,
		GATE_LEN_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		CLOCK_OUTPUT,
		RESET_OUTPUT,
		MOD_CV_1_OUTPUT,
		MOD_CV_2_OUTPUT,
		MOD_CV_3_OUTPUT,
		MOD_CV_4_OUTPUT,
		CV_1_OUTPUT,
		CV_2_OUTPUT,
		CV_3_OUTPUT,
		CV_4_OUTPUT,
		MOD_GATE_1_OUTPUT,
		MOD_GATE_2_OUTPUT,
		MOD_GATE_3_OUTPUT,
		MOD_GATE_4_OUTPUT,
		GATE_1_OUTPUT,
		GATE_2_OUTPUT,
		GATE_3_OUTPUT,
		GATE_4_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		SCALE_A_LIGHT,
		SCALE_A_LIGHT,
		NUM_LIGHTS
	};

	SDOrcasHeart() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(LENGTH_PARAM, 0.f, 1.f, 0.f, "");
		configParam(TRANSPOSE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(ALGO_X_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SHIFT_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SPEED_PARAM, 0.f, 1.f, 0.f, "");
		configParam(GATE_LEN_PARAM, 0.f, 1.f, 0.f, "");
		configParam(ALGO_Y_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SPACE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_A_PARAM, 0.f, 1.f, 0.f, "");
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
		configParam(SCALE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_17_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_18_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_20_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_22_PARAM, 0.f, 1.f, 0.f, "");
		configParam(SCALE_24_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs &args) override {
	}
};


struct SDOrcasHeartWidget : ModuleWidget {
	SDOrcasHeartWidget(SDOrcasHeart *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeart.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(16.124, 18.394)), module, SDOrcasHeart::LENGTH_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(136.276, 18.394)), module, SDOrcasHeart::TRANSPOSE_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(40.768, 23.622)), module, SDOrcasHeart::ALGO_X_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(111.632, 23.622)), module, SDOrcasHeart::SHIFT_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(16.124, 42.95)), module, SDOrcasHeart::SPEED_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(136.276, 42.95)), module, SDOrcasHeart::GATE_LEN_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(40.768, 48.178)), module, SDOrcasHeart::ALGO_Y_PARAM));
		addParam(createParamCentered<SDLargeKnob>(mm2px(Vec(111.632, 48.178)), module, SDOrcasHeart::SPACE_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(56.841, 64.569)), module, SDOrcasHeart::SCALE_2_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(65.795, 64.569)), module, SDOrcasHeart::SCALE_4_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(83.702, 64.569)), module, SDOrcasHeart::SCALE_7_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(92.656, 64.569)), module, SDOrcasHeart::SCALE_9_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(101.61, 64.569)), module, SDOrcasHeart::SCALE_11_PARAM));
		addParam(createParamCentered<SDButton>(mm2px(Vec(119.411, 66.664)), module, SDOrcasHeart::SCALE_A_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(52.365, 69.289)), module, SDOrcasHeart::SCALE_1_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(61.318, 69.289)), module, SDOrcasHeart::SCALE_3_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(70.272, 69.289)), module, SDOrcasHeart::SCALE_5_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(79.226, 69.289)), module, SDOrcasHeart::SCALE_6_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(88.179, 69.289)), module, SDOrcasHeart::SCALE_8_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(97.133, 69.289)), module, SDOrcasHeart::SCALE_10_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(106.087, 69.289)), module, SDOrcasHeart::SCALE_12_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(56.312, 80.352)), module, SDOrcasHeart::SCALE_14_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(65.266, 80.352)), module, SDOrcasHeart::SCALE_16_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(83.173, 80.352)), module, SDOrcasHeart::SCALE_19_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(92.127, 80.352)), module, SDOrcasHeart::SCALE_21_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(101.081, 80.352)), module, SDOrcasHeart::SCALE_23_PARAM));
		addParam(createParamCentered<SDMomentaryButton>(mm2px(Vec(33.609, 82.447)), module, SDOrcasHeart::SCALE_PARAM));
		addParam(createParamCentered<SDButton>(mm2px(Vec(119.411, 82.447)), module, SDOrcasHeart::SCALE_B_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(51.835, 85.072)), module, SDOrcasHeart::SCALE_13_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(60.789, 85.072)), module, SDOrcasHeart::SCALE_15_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(69.743, 85.072)), module, SDOrcasHeart::SCALE_17_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(78.696, 85.072)), module, SDOrcasHeart::SCALE_18_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(87.65, 85.072)), module, SDOrcasHeart::SCALE_20_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(96.604, 85.072)), module, SDOrcasHeart::SCALE_22_PARAM));
		addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(105.557, 85.072)), module, SDOrcasHeart::SCALE_24_PARAM));

		addInput(createInputCentered<SDPort>(mm2px(Vec(11.567, 66.664)), module, SDOrcasHeart::CLOCK_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(22.588, 66.664)), module, SDOrcasHeart::EXP_1_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(33.609, 66.664)), module, SDOrcasHeart::EXP_2_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(130.506, 66.664)), module, SDOrcasHeart::SCALE_A_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(11.567, 82.447)), module, SDOrcasHeart::RESET_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(22.588, 82.447)), module, SDOrcasHeart::SCALE_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(130.506, 82.447)), module, SDOrcasHeart::SCALE_B_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(59.986, 103.413)), module, SDOrcasHeart::LENGTH_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(71.007, 103.413)), module, SDOrcasHeart::ALGO_X_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(82.027, 103.413)), module, SDOrcasHeart::SHIFT_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(93.048, 103.413)), module, SDOrcasHeart::TRANSPOSE_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(59.986, 119.196)), module, SDOrcasHeart::SPEED_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(71.007, 119.196)), module, SDOrcasHeart::ALGO_Y_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(82.027, 119.196)), module, SDOrcasHeart::SPACE_INPUT));
		addInput(createInputCentered<SDPort>(mm2px(Vec(93.048, 119.196)), module, SDOrcasHeart::GATE_LEN_INPUT));

		addOutput(createOutputCentered<SDPort>(mm2px(Vec(141.467, 66.664)), module, SDOrcasHeart::CLOCK_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(141.467, 82.447)), module, SDOrcasHeart::RESET_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(11.567, 103.413)), module, SDOrcasHeart::MOD_CV_1_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(22.588, 103.413)), module, SDOrcasHeart::MOD_CV_2_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(33.609, 103.413)), module, SDOrcasHeart::MOD_CV_3_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(44.629, 103.413)), module, SDOrcasHeart::MOD_CV_4_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(108.315, 103.413)), module, SDOrcasHeart::CV_1_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(119.411, 103.413)), module, SDOrcasHeart::CV_2_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(130.506, 103.413)), module, SDOrcasHeart::CV_3_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(141.467, 103.413)), module, SDOrcasHeart::CV_4_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(11.567, 119.196)), module, SDOrcasHeart::MOD_GATE_1_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(22.588, 119.196)), module, SDOrcasHeart::MOD_GATE_2_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(33.609, 119.196)), module, SDOrcasHeart::MOD_GATE_3_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(44.629, 119.196)), module, SDOrcasHeart::MOD_GATE_4_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(108.405, 119.196)), module, SDOrcasHeart::GATE_1_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(119.425, 119.196)), module, SDOrcasHeart::GATE_2_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(130.446, 119.196)), module, SDOrcasHeart::GATE_3_OUTPUT));
		addOutput(createOutputCentered<SDPort>(mm2px(Vec(141.467, 119.196)), module, SDOrcasHeart::GATE_4_OUTPUT));

		addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(45.478, 66.664)), module, SDOrcasHeart::SCALE_A_LIGHT));
		addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(45.478, 82.447)), module, SDOrcasHeart::SCALE_A_LIGHT));

		// mm2px(Vec(35.004, 41.903))
		addChild(createWidget<Widget>(mm2px(Vec(58.698, 13.988))));
	}
};


Model *modelSDOrcasHeart = createModel<SDOrcasHeart, SDOrcasHeartWidget>("SDOrcasHeart");