#include "plugin.hpp"

#include <math.h> 
#include <string> 
#include <jansson.h>

#include "LedScreen.hpp"
#include "SharedComponents.hpp"

#define DISPLAYLINES 8

#define SCALELEN 12
#define SCALECOUNT 2
#define NOTECOUNT 4
#define MODCOUNT 4
#define TRACKCOUNT 4
#define GATEPRESETCOUNT 16
#define SPACEPRESETCOUNT 16
#define PARAMCYCLE 4

struct SDTextDisplay : LedDisplay {

	LedDisplayChoice* lines[DISPLAYLINES];
    
    SDTextDisplay() {
        Vec pos;

        for (int i = 0; i < DISPLAYLINES; i++) {
            lines[i] = createWidget<LedDisplayChoice>(pos);
            lines[i]->box.size.x = box.size.x;
            addChild(lines[i]);
            pos.y += 14;
        }
    }
};

struct SDOrcasHeart : Module {

    int gatePresets[GATEPRESETCOUNT][NOTECOUNT] = {
        {0b0001, 0b0010, 0b0100, 0b1000},
        {0b0011, 0b0010, 0b0101, 0b1000},
        {0b0011, 0b0110, 0b1101, 0b1000},
        {0b0111, 0b0110, 0b1101, 0b1001},

        {0b0111, 0b0101, 0b1101, 0b1010},
        {0b1111, 0b0101, 0b1110, 0b1010},
        {0b1101, 0b1101, 0b1010, 0b1011},
        {0b1101, 0b1000, 0b0110, 0b1101},

        {0b1001, 0b1100, 0b1110, 0b0111},
        {0b1100, 0b0101, 0b0110, 0b0111},
        {0b1100, 0b0110, 0b0110, 0b1100},
        {0b0101, 0b1010, 0b0110, 0b1101},

        {0b0101, 0b1001, 0b0110, 0b0101},
        {0b0110, 0b0101, 0b0110, 0b1101},
        {0b1100, 0b0011, 0b0110, 0b1100},
        {0b1001, 0b0010, 0b0101, 0b1000}
    };
    
    int spacePresets[SPACEPRESETCOUNT] = {
        0b0000, 0b0001, 0b0010, 0b0100,
        0b1000, 0b0011, 0b0101, 0b1001,
        0b0110, 0b1010, 0b1100, 0b0111,
        0b1011, 0b1101, 0b1110, 0b1111
    };

    enum ParamIds {
        LENGTH_PARAM,
        SPEED_PARAM,
        ALGO_X_PARAM,
        ALGO_Y_PARAM,
        SHIFT_PARAM,
        SPACE_PARAM,
        TRANSPOSE_PARAM,
        GATE_LEN_PARAM,
        SCALE_PARAM,
        // params that have corresponding inputs should be above
        SCALE_A_PARAM,
        SCALE_B_PARAM,
        SCALE_1_PARAM,
        SCALE_2_PARAM,
        SCALE_3_PARAM,
        SCALE_4_PARAM,
        SCALE_5_PARAM,
        SCALE_6_PARAM,
        SCALE_7_PARAM,
        SCALE_8_PARAM,
        SCALE_9_PARAM,
        SCALE_10_PARAM,
        SCALE_11_PARAM,
        SCALE_12_PARAM,
        SCALE_13_PARAM,
        SCALE_14_PARAM,
        SCALE_15_PARAM,
        SCALE_16_PARAM,
        SCALE_17_PARAM,
        SCALE_18_PARAM,
        SCALE_19_PARAM,
        SCALE_20_PARAM,
        SCALE_21_PARAM,
        SCALE_22_PARAM,
        SCALE_23_PARAM,
        SCALE_24_PARAM,
        NUM_PARAMS
    };

    enum InputIds {
        LENGTH_INPUT,
        SPEED_INPUT,
        ALGO_X_INPUT,
        ALGO_Y_INPUT,
        SHIFT_INPUT,
        SPACE_INPUT,
        TRANSPOSE_INPUT,
        GATE_LEN_INPUT,
        SCALE_INPUT,
        SCALE_A_INPUT,
        SCALE_B_INPUT,
        // inputs that have corresponding params should be above
        CLOCK_INPUT,
        RESET_INPUT,
        EXP_1_INPUT,
        EXP_2_INPUT,
        NUM_INPUTS
    };

    enum OutputIds {
        CLOCK_OUTPUT,
        RESET_OUTPUT,
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        GATE_1_OUTPUT,
        GATE_2_OUTPUT,
        GATE_3_OUTPUT,
        GATE_4_OUTPUT,
        MOD_CV_1_OUTPUT,
        MOD_CV_2_OUTPUT,
        MOD_CV_3_OUTPUT,
        MOD_CV_4_OUTPUT,
        MOD_GATE_1_OUTPUT,
        MOD_GATE_2_OUTPUT,
        MOD_GATE_3_OUTPUT,
        MOD_GATE_4_OUTPUT,
        NUM_OUTPUTS
    };
    enum LightIds {
        SCALE_A_LIGHT,
        SCALE_B_LIGHT,
        NUM_LIGHTS
    };

    SDOrcasHeart() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(LENGTH_PARAM, 1.f, 32.f, 8.f, "Length");
        configParam(SPEED_PARAM, 20.f, 2000.f, 400.f, "Speed");
        configParam(ALGO_X_PARAM, 0.f, 127.f, 0.f, "Algo X");
        configParam(ALGO_Y_PARAM, 0.f, 127.f, 0.f, "Algo Y");
        configParam(SHIFT_PARAM, 0.f, 12.f, 0.f, "Shift");
        configParam(SPACE_PARAM, 0.f, SPACEPRESETCOUNT - 1.f, 0.f, "Space");
        configParam(TRANSPOSE_PARAM, -2.f, 2.f, 0.f, "Transpose");
        configParam(GATE_LEN_PARAM, 0.1f, 4.0f, 1.f, "Gate Length");
        
        configButton(SCALE_PARAM, "Scale A/B");
        configSwitch(SCALE_A_PARAM, 0, 1, 1, "Octave A", {"Down", "Up"});
        configSwitch(SCALE_B_PARAM, 0, 1, 0, "Octave B", {"Down", "Up"});
        
        configInput(LENGTH_INPUT, "Length");
        configInput(SPEED_INPUT, "Speed");
        configInput(ALGO_X_INPUT, "Algo X");
        configInput(ALGO_Y_INPUT, "Algo Y");
        configInput(SHIFT_INPUT, "Shift");
        configInput(SPACE_INPUT, "Space");
        configInput(TRANSPOSE_INPUT, "Transpose");
        configInput(GATE_LEN_INPUT, "Gate Length");
        configInput(SCALE_INPUT, "Scale A/B");
        configInput(SCALE_A_INPUT, "+ Octave A");
        configInput(SCALE_B_INPUT, "+ Octave B");
        configInput(CLOCK_INPUT, "Clock");
        configInput(RESET_INPUT, "Reset");
        configInput(EXP_1_INPUT, "Expansion 1 (unused)");
        configInput(EXP_2_INPUT, "Expansion 2 (unused)");
        
        configOutput(CLOCK_OUTPUT, "Clock");
        configOutput(RESET_OUTPUT, "Reset");
        configOutput(CV_1_OUTPUT, "Note CV #1 1V/Oct");
        configOutput(CV_2_OUTPUT, "Note CV #2 1V/Oct");
        configOutput(CV_3_OUTPUT, "Note CV #3 1V/Oct");
        configOutput(CV_4_OUTPUT, "Note CV #4 1V/Oct");
        configOutput(GATE_1_OUTPUT, "Note Gate #1");
        configOutput(GATE_2_OUTPUT, "Note Gate #2");
        configOutput(GATE_3_OUTPUT, "Note Gate #3");
        configOutput(GATE_4_OUTPUT, "Note Gate #4");
        configOutput(MOD_CV_1_OUTPUT, "Modulation CV #1");
        configOutput(MOD_CV_2_OUTPUT, "Modulation CV #2");
        configOutput(MOD_CV_3_OUTPUT, "Modulation CV #3");
        configOutput(MOD_CV_4_OUTPUT, "Modulation CV #4");
        configOutput(MOD_GATE_1_OUTPUT, "Modulation Gate #1");
        configOutput(MOD_GATE_2_OUTPUT, "Modulation Gate #2");
        configOutput(MOD_GATE_3_OUTPUT, "Modulation Gate #3");
        configOutput(MOD_GATE_4_OUTPUT, "Modulation Gate #4");
        
        configLight(SCALE_A_LIGHT, "Scale A Selected");
        configLight(SCALE_B_LIGHT, "Scale B Selected");
        
        for (int i = 0; i < SCALELEN * SCALECOUNT; i++)
            configSwitch(SCALE_1_PARAM + i, 0, 1, 0, "Note", {"Off", "On"});
        
        updateScaleLeds();
    }

    LedScreen *ledScreen;
    SDTextDisplay *textDisplay;

    dsp::SchmittTrigger clockIn, resetIn, scaleSwitchTrig, scaleInputTrig;
    dsp::PulseGenerator clockOut, resetOut;
    
    float internalClock = 2.f, speed, gateLength, transpose;
    int length, speedBPM, algoX, algoY, shift, space;

    int scales[SCALECOUNT][SCALELEN] = {};
    int scaleCount[SCALECOUNT] = {};
    int scale = 0;

    int globalCounter = 0;
    int spaceCounter = 0;
    int paramUpdateCount = PARAMCYCLE;

    int counter[TRACKCOUNT] = {0, 0, 0, 0};
    int divisor[TRACKCOUNT] = {2, 3, 5, 4};
    int phase[TRACKCOUNT]   = {2, 3, 5, 4};
    int weights[TRACKCOUNT] = {1, 2, 4, 7};
    int shifts[TRACKCOUNT] = {0, 0, 0, 0};

    int trackOn[TRACKCOUNT] = {0, 0, 0, 0};
    int weightOn[TRACKCOUNT] = {0, 0, 0, 0};
    int totalWeight = 0;

    int notes[NOTECOUNT];
    bool gateOn[NOTECOUNT] = {0, 0, 0, 0};
    bool gateChanged[NOTECOUNT] = {1, 1, 1, 1};
    float gateTimer[NOTECOUNT] = {0, 0, 0, 0};

    int modCvs[MODCOUNT];
    bool modGateOn[MODCOUNT] = {0, 0, 0, 0};
    bool modGateChanged[MODCOUNT] = {1, 1, 1, 1};
    
    float getValue(int param) {
        float min = paramQuantities[param]->minValue;
        float max = paramQuantities[param]->maxValue;
        float i = inputs[param].getVoltage() * (max - min) / 10.f + params[param].getValue();
        
        if (min > max) {
            float t = min;
            min = max;
            max = t;
        }
        if (i < min) i = min; else if (i > max) i = max;
        
        return i;
    }
    
    void updateScaleLeds() {
        if (scale) {
            lights[SCALE_A_LIGHT].setBrightness(0.f);
            lights[SCALE_B_LIGHT].setBrightness(1.f);
        } else {
            lights[SCALE_A_LIGHT].setBrightness(1.f);
            lights[SCALE_B_LIGHT].setBrightness(0.f);
        }
    }

    void processScaleSwitch() {
        if (scaleSwitchTrig.process(params[SCALE_PARAM].getValue() > 0.f) ||
            scaleInputTrig.process(rescale(inputs[SCALE_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f))) {
            scale = scale ? 0 : 1;
            updateScaleLeds();
        }
    }
        
    void updateScales() {
        for (int s = 0; s < SCALECOUNT; s++) {
            scaleCount[s] = 0;
            for (int i = 0; i < SCALELEN; i++) {
                if (params[SCALE_1_PARAM + i + s * SCALELEN].getValue() > 0) { 
                    scales[s][scaleCount[s]++] = i;
                }
            }
        }
    }

    void updateParameters() {
        length = getValue(LENGTH_PARAM);
        speedBPM = round(getValue(SPEED_PARAM));
        speed = 60.f / speedBPM;
        algoX = round(getValue(ALGO_X_PARAM));
        algoY = round(getValue(ALGO_Y_PARAM));
        shift = round(getValue(SHIFT_PARAM));
        space = round(getValue(SPACE_PARAM));
        transpose = getValue(TRANSPOSE_PARAM);
        gateLength = getValue(GATE_LEN_PARAM);
    }

    void updateTrackParameters() {
        divisor[0] = (algoX & 3) + 1;
        phase[0] = algoX >> 5;
        
        for (int i = 1; i < TRACKCOUNT; i++) {
            if (algoX & (1 << (i + 2))) divisor[i] = divisor[i-1] + 1; else divisor[i] = divisor[i-1] - 1;
            if (divisor[i] < 0) divisor[i] = 1 - divisor[i]; 
            if (divisor[i] == 0) divisor[i] = i + 2;
            phase[i] = ((algoX & (0b11 << i)) + i) % divisor[i];
        }
        
        for (int i = 0; i < TRACKCOUNT; i++) shifts[i] = getValue(SHIFT_PARAM);
    }
    
    void updateCounters() {
        if (resetIn.process(rescale(inputs[RESET_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f))) {
            spaceCounter = globalCounter = 0;
            for (int i = 0; i < TRACKCOUNT; i++) counter[i] = 0;
            resetOut.trigger(1e-3);
        } else {
            if (++spaceCounter >= 16) spaceCounter = 0;

            if (++globalCounter >= length) {
                globalCounter = 0;
                for (int i = 0; i < TRACKCOUNT; i++) counter[i] = 0;
                resetOut.trigger(1e-3);
            } else {
                for (int i = 0; i < TRACKCOUNT; i++) counter[i]++;
            }
        }
        
        totalWeight = 0;
        for (int i = 0; i < TRACKCOUNT; i++) {
            trackOn[i] = ((counter[i] + phase[i]) / divisor[i]) & 1;
            weightOn[i] = trackOn[i] ? weights[i] : 0;
            totalWeight += weightOn[i];
        }
        
        for (int i = 0; i < NOTECOUNT; i++) { 
            shifts[i] = shift;
            if (shift > SCALELEN / 2) shifts[i] += i;
        }
    }
    
    void updateMod() {
        for (int i = 0; i < MODCOUNT; i++) modGateOn[i] = trackOn[i % TRACKCOUNT];

        modCvs[0] = totalWeight + weightOn[0];
        modCvs[1] = weights[1] * (trackOn[3] + trackOn[2]) + weights[2] * (trackOn[0] + trackOn[2]);
        modCvs[2] = weights[0] * (trackOn[2] + trackOn[1]) + weights[3] * (trackOn[0] + trackOn[3]);
        modCvs[3] = weights[1] * (trackOn[1] + trackOn[2]) + weights[2] * (trackOn[2]  + trackOn[3]) + weights[3] * (trackOn[3] + trackOn[2]);
        
        for (int i = 0; i < MODCOUNT; i++) modCvs[i] %= 10;
    }

    void calculateNote(int n) {
        int mask = algoY >> 3;

        notes[n] = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) notes[n] += weightOn[j];
        }

        if (algoY & 1) notes[n] += weightOn[(n + 1) % TRACKCOUNT];
        if (algoY & 2) notes[n] += weightOn[(n + 2) % TRACKCOUNT];
        if (algoY & 4) notes[n] += weightOn[(n + 3) % TRACKCOUNT];
        
        notes[n] += shifts[n];
    }
    
    void calculateNextNote(int n) {
        int mask = gatePresets[algoY >> 3][n];
        if (mask == 0) mask = 0b0101;
        for (int i = 0; i < n; i++) mask = ((mask & 1) << 3) | (mask >> 1);
        
        int gate = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) gate = 1;
            // if (mask & (1 << j)) gate = 1;
        }

        if (algoY & 1) gate ^= trackOn[n % TRACKCOUNT] << 1;
        if (algoY & 2) gate ^= trackOn[(n + 2) % TRACKCOUNT] << 2;
        if (algoY & 4) gate ^= trackOn[(n + 3) % TRACKCOUNT] << 3;

        bool previousGatesOn = 1;
        for (int i = 0; i < NOTECOUNT - 1; i++) previousGatesOn &= gateChanged[i] & gateOn[i];
        if (n == NOTECOUNT - 1 && previousGatesOn) gate = 0;
        
        gateChanged[n] = gateOn[n] != gate;
        gateOn[n] = gate;
        if (gateChanged[n]) {
            gateTimer[n] = speed * gateLength;
            calculateNote(n);
        }
    }

    void process(const ProcessArgs &args) override {
        bool advance = 0;
        if (inputs[CLOCK_INPUT].active) {
            advance = clockIn.process(rescale(inputs[CLOCK_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
        } else {
            internalClock += args.sampleTime;
            if (internalClock >= speed) {
                advance = 1;
                internalClock = 0;
            }
        }
        
        if (advance || ++paramUpdateCount >= PARAMCYCLE) {
            updateParameters();
            updateTrackParameters();
            processScaleSwitch();
            updateScales();
            paramUpdateCount = 0;
        }

        if (advance) {
            updateCounters();
            updateMod();
            for (int n = 0; n < NOTECOUNT; n++) calculateNextNote(n);
            updateDisplay();
            clockOut.trigger(1e-3);
        }
        
        float trans = transpose;
        if ((scale == 0 && getValue(SCALE_A_PARAM) > 0) || (scale == 1 && getValue(SCALE_B_PARAM) > 0)) trans += 1.f;
        
        for (int n = 0; n < NOTECOUNT; n++) {
            if (scaleCount[scale] == 0) {
                outputs[CV_1_OUTPUT + n].setVoltage(scales[scale][0] / 12.f);
                outputs[GATE_1_OUTPUT + n].setVoltage(0);
            } else {
                outputs[CV_1_OUTPUT + n].setVoltage(scales[scale][notes[n] % scaleCount[scale]] / 12.f + std::min(2, notes[n] / 12) + trans);
                int sp = spacePresets[(space | n) % SPACEPRESETCOUNT];
                if (sp & spaceCounter) {
                    outputs[GATE_1_OUTPUT + n].setVoltage(0);
                } else {
                    if (gateTimer[n] > 0) gateTimer[n] -= args.sampleTime;
                    if (gateTimer[n] < 0) gateTimer[n] = 0;
                    float g = 10.0; // (float)(modCvs[n] % 8) / 4.0 + 5.0;
                    outputs[GATE_1_OUTPUT + n].setVoltage(gateTimer[n] > 0 ? g : 0);
                }
            }
        }
        
        for (int i = 0; i < MODCOUNT; i++) {
            outputs[MOD_GATE_1_OUTPUT + i].setVoltage(modGateOn[i] ? 10.f : 0.f);
            outputs[MOD_CV_1_OUTPUT + i].setVoltage((float)(modCvs[i] % 8) / 7.f * 10.f);
        }
        
        outputs[CLOCK_OUTPUT].setVoltage(clockOut.process(args.sampleTime) ? 10.f : 0.f);
        outputs[RESET_OUTPUT].setVoltage(resetOut.process(args.sampleTime) ? 10.f : 0.f);
    }

    json_t *dataToJson() override {
        json_t *rootJ = json_object();
        json_object_set_new(rootJ, "selected_scale", json_integer(scale));
        return rootJ;
    }

    void dataFromJson(json_t *rootJ) override {
        json_t *scaleJ = json_object_get(rootJ, "selected_scale");
        if (scaleJ) {
            scale = json_integer_value(scaleJ);
            updateScaleLeds();
        }
    }

    std::stringstream stream;
    void updateDisplay() {
        textDisplay->lines[0]->text = "LENGTH: " + std::to_string(length);
        textDisplay->lines[1]->text = "SPEED : " + std::to_string(speedBPM);
        textDisplay->lines[2]->text = "ALGO X: " + std::to_string(algoX);
        textDisplay->lines[3]->text = "ALGO Y: " + std::to_string(algoY);
        textDisplay->lines[4]->text = "SHIFT : " + std::to_string(shift);
        textDisplay->lines[5]->text = "SPACE : " + std::to_string(space);
        textDisplay->lines[6]->text = "TRANS : " + (transpose < 0 ? std::to_string(transpose).substr(0, 5) : std::to_string(transpose).substr(0, 4));
        textDisplay->lines[7]->text = "GATE L: " + std::to_string(gateLength).substr(0, 3);
    }
};


struct SDOrcasHeartWidget : ModuleWidget {
    SDOrcasHeartWidget(SDOrcasHeart *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeart6.svg")));

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
        addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(45.478, 82.447)), module, SDOrcasHeart::SCALE_B_LIGHT));

        Vec displayPos = Vec(58.698, 13.988);
        Vec displaySize = Vec(35.004, 41.903);

        SDTextDisplay *textDisplay = createWidget<SDTextDisplay>(mm2px(displayPos));
        textDisplay->box.size = mm2px(displaySize);
        addChild(textDisplay);
        if (module) module->textDisplay = textDisplay;

        /*
        float ledWidth = 8.f;
        float ledHeight = 8.f;
        float ledX = displayPos.x + displaySize.x - ledWidth - 3.f;
        float ledY = displayPos.y + (displaySize.y - ledHeight) / 2.f;
        LedScreen *ledScreen = new LedScreen(module);
        ledScreen->box.pos = mm2px(Vec(ledX, ledY));
        ledScreen->box.size = mm2px(Vec(ledWidth, ledHeight));
        addChild(ledScreen);
        if (module) module->ledScreen = ledScreen;
        */
    }
};

Model *modelSDOrcasHeart = createModel<SDOrcasHeart, SDOrcasHeartWidget>("SDOrcasHeart");