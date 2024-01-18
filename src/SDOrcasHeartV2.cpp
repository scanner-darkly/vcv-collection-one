#include "plugin.hpp"

#include <math.h> 
#include <string> 

#include "SharedComponents.hpp"

#define SCALELEN 12
#define SCALECOUNT 2
#define NOTECOUNT 8
#define HISTORYCOUNT 8
#define MODCOUNT 4
#define TRACKCOUNT 8
#define GATEPRESETCOUNT 16
#define SPACEPRESETCOUNT 16

struct SDOrcasHeartV2 : Module {

    int gatePresets[GATEPRESETCOUNT][NOTECOUNT] = {
        {0b0001, 0b0010, 0b0100, 0b1000, 0b0000, 0b0001, 0b0101, 0b1010},
        {0b0011, 0b0010, 0b0101, 0b1000, 0b0001, 0b0010, 0b0100, 0b0100},
        {0b0011, 0b0110, 0b1101, 0b1000, 0b0010, 0b0100, 0b0100, 0b0001},
        {0b0111, 0b0110, 0b1101, 0b1001, 0b0100, 0b1000, 0b0010, 0b0001},

        {0b0111, 0b0101, 0b1101, 0b1010, 0b1001, 0b0101, 0b0010, 0b1001},
        {0b1111, 0b0101, 0b1110, 0b1010, 0b0110, 0b1010, 0b0011, 0b1001},
        {0b1101, 0b1101, 0b1010, 0b1011, 0b1010, 0b0110, 0b0011, 0b1100},
        {0b1101, 0b1000, 0b0110, 0b1101, 0b1100, 0b0011, 0b0010, 0b0100},

        {0b1001, 0b1100, 0b1110, 0b0111, 0b1000, 0b0001, 0b0100, 0b0010},
        {0b1100, 0b0101, 0b0110, 0b0111, 0b0100, 0b1000, 0b1010, 0b0110},
        {0b1100, 0b0110, 0b0110, 0b1100, 0b0010, 0b0100, 0b1001, 0b1110},
        {0b0101, 0b1010, 0b0110, 0b1101, 0b0001, 0b0010, 0b0110, 0b1001},

        {0b0101, 0b1001, 0b0110, 0b0101, 0b1101, 0b1011, 0b0010, 0b0001},
        {0b0110, 0b0101, 0b0110, 0b1101, 0b1100, 0b0011, 0b0001, 0b0010},
        {0b1100, 0b0011, 0b0110, 0b1100, 0b0110, 0b0110, 0b1000, 0b0010},
        {0b1001, 0b0010, 0b0101, 0b1000, 0b0010, 0b0100, 0b1010, 0b0001}
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
        ROTATE_PARAM,
        XMOD_TYPE_PARAM,
        SPREAD_PARAM,
        XMOD_PARAM,
        SCALE_PARAM,
        SCALE_A_PARAM,
        SCALE_B_PARAM,
        SCALE_A_OCT_PARAM,
        SCALE_B_OCT_PARAM,
        // SCALE_ outputs must be arranged consecutively 
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
        ROTATE_INPUT,
        SPREAD_INPUT,
        XMOD_TYPE_INPUT,
        XMOD_INPUT,

        SCALE_INPUT,
        SCALE_A_OCT_INPUT,
        SCALE_B_OCT_INPUT,
        SCALE_A_INPUT,
        SCALE_B_INPUT,

        CLOCK_INPUT,
        RESET_INPUT,
        NUM_INPUTS
    };

    enum OutputIds {
        CLOCK_OUTPUT,
        RESET_OUTPUT,
        // CV_ and GATE_ outputs must be arranged consecutively 
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        CV_5_OUTPUT,
        CV_6_OUTPUT,
        CV_7_OUTPUT,
        CV_8_OUTPUT,
        GATE_1_OUTPUT,
        GATE_2_OUTPUT,
        GATE_3_OUTPUT,
        GATE_4_OUTPUT,
        GATE_5_OUTPUT,
        GATE_6_OUTPUT,
        GATE_7_OUTPUT,
        GATE_8_OUTPUT,
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

    SDOrcasHeartV2() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        configParam(SCALE_A_PARAM, 1.f, 32.f, 1.f, "Scale A");
        getParamQuantity(SCALE_A_PARAM)->snapEnabled = true;
        configParam(SCALE_B_PARAM, 1.f, 32.f, 1.f, "Scale B");
        getParamQuantity(SCALE_B_PARAM)->snapEnabled = true;
        
        configParam(SPEED_PARAM, 20.f, 2000.f, 400.f, "Speed");
        configParam(LENGTH_PARAM, 1.f, 32.f, 8.f, "Length");
        getParamQuantity(LENGTH_PARAM)->snapEnabled = true;
        configParam(ALGO_X_PARAM, 0.f, 127.f, 1.f, "Algo X");
        getParamQuantity(ALGO_X_PARAM)->snapEnabled = true;
        configParam(ALGO_Y_PARAM, 0.f, 127.f, 1.f, "Algo Y");
        getParamQuantity(ALGO_Y_PARAM)->snapEnabled = true;
        configParam(SHIFT_PARAM, 0.f, 12.f, 0.f, "Shift");
        getParamQuantity(SHIFT_PARAM)->snapEnabled = true;
        configParam(SPACE_PARAM, 0.f, SPACEPRESETCOUNT - 1.f, 0.f, "Space");
        getParamQuantity(SPACE_PARAM)->snapEnabled = true;
        configParam(ROTATE_PARAM, -7.f, 7.f, 0.f, "Rotate");
        getParamQuantity(ROTATE_PARAM)->snapEnabled = true;
        configParam(SPREAD_PARAM, -8.f, 8.f, 0.f, "Spread");
        configParam(XMOD_TYPE_PARAM, 1.f, 16.f, 1.f, "Crossmod Type");
        getParamQuantity(XMOD_TYPE_PARAM)->snapEnabled = true;
        configParam(XMOD_PARAM, 0.f, 1.f, 0.f, "Crossmod Amount");
        configParam(TRANSPOSE_PARAM, -3.f, 3.f, 0.f, "Transpose");
        configParam(GATE_LEN_PARAM, 0.1f, 4.0f, 1.f, "Gate Length");

        configButton(SCALE_PARAM, "Scale A/B");
        configSwitch(SCALE_A_OCT_PARAM, 0, 1, 1, "Octave A", { "Down", "Up" });
        configSwitch(SCALE_B_OCT_PARAM, 0, 1, 0, "Octave B", { "Down", "Up" });

        configInput(SCALE_A_INPUT, "Scale A");
        configInput(SCALE_B_INPUT, "Scale B");
        configInput(SCALE_INPUT, "Scale A/B");
        configInput(SCALE_A_OCT_INPUT, "+ Octave A");
        configInput(SCALE_B_OCT_INPUT, "+ Octave B");

        configInput(CLOCK_INPUT, "Clock");
        configInput(RESET_INPUT, "Reset");

        configInput(SPEED_INPUT, "Speed");
        configInput(LENGTH_INPUT, "Length");
        configInput(ALGO_X_INPUT, "Algo X");
        configInput(ALGO_Y_INPUT, "Algo Y");
        configInput(SHIFT_INPUT, "Shift");
        configInput(SPACE_INPUT, "Space");
        configInput(ROTATE_INPUT, "Rotate");
        configInput(SPREAD_INPUT, "Spread");
        configInput(XMOD_TYPE_INPUT, "Crossmod Type");
        configInput(XMOD_INPUT, "Crossmod Amount");
        configInput(TRANSPOSE_INPUT, "Transpose");
        configInput(GATE_LEN_INPUT, "Gate Length");

        configOutput(CLOCK_OUTPUT, "Clock");
        configOutput(RESET_OUTPUT, "Reset");
        configOutput(CV_1_OUTPUT, "Note CV #1 1V/Oct");
        configOutput(CV_2_OUTPUT, "Note CV #2 1V/Oct");
        configOutput(CV_3_OUTPUT, "Note CV #3 1V/Oct");
        configOutput(CV_4_OUTPUT, "Note CV #4 1V/Oct");
        configOutput(CV_5_OUTPUT, "Note CV #5 1V/Oct");
        configOutput(CV_6_OUTPUT, "Note CV #6 1V/Oct");
        configOutput(CV_7_OUTPUT, "Note CV #7 1V/Oct");
        configOutput(CV_8_OUTPUT, "Note CV #8 1V/Oct");
        configOutput(GATE_1_OUTPUT, "Note Gate #1");
        configOutput(GATE_2_OUTPUT, "Note Gate #2");
        configOutput(GATE_3_OUTPUT, "Note Gate #3");
        configOutput(GATE_4_OUTPUT, "Note Gate #4");
        configOutput(GATE_5_OUTPUT, "Note Gate #5");
        configOutput(GATE_6_OUTPUT, "Note Gate #6");
        configOutput(GATE_7_OUTPUT, "Note Gate #7");
        configOutput(GATE_8_OUTPUT, "Note Gate #8");
        configOutput(MOD_CV_1_OUTPUT, "Modulation CV #1");
        configOutput(MOD_CV_2_OUTPUT, "Modulation CV #2");
        configOutput(MOD_CV_3_OUTPUT, "Modulation CV #3");
        configOutput(MOD_CV_4_OUTPUT, "Modulation CV #4");
        configOutput(MOD_GATE_1_OUTPUT, "Modulation Gate #1");
        configOutput(MOD_GATE_2_OUTPUT, "Modulation Gate #2");
        configOutput(MOD_GATE_3_OUTPUT, "Modulation Gate #3");
        configOutput(MOD_GATE_4_OUTPUT, "Modulation Gate #4");
        
        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        int scaleOffset;
        for (int i = 0; i < SCALECOUNT; i++) {
            scaleOffset = SCALE_1_PARAM + i * SCALELEN;

            configSwitch(scaleOffset + 0, 0, 1, i == 0, "C", { "Off", "On" });
            configSwitch(scaleOffset + 1, 0, 1, 0, "C#", { "Off", "On" });
            configSwitch(scaleOffset + 2, 0, 1, i == 0, "D", { "Off", "On" });
            configSwitch(scaleOffset + 3, 0, 1, 0, "D#", { "Off", "On" });

            configSwitch(scaleOffset + 4, 0, 1, i == 0, "E", { "Off", "On" });
            configSwitch(scaleOffset + 5, 0, 1, 0, "F", { "Off", "On" });
            configSwitch(scaleOffset + 6, 0, 1, 0, "F#", { "Off", "On" });
            configSwitch(scaleOffset + 7, 0, 1, 0, "G", { "Off", "On" });

            configSwitch(scaleOffset + 8, 0, 1, 0, "G#", { "Off", "On" });
            configSwitch(scaleOffset + 9, 0, 1, 0, "A", { "Off", "On" });
            configSwitch(scaleOffset + 10, 0, 1, 0, "A#", { "Off", "On" });
            configSwitch(scaleOffset + 11, 0, 1, 0, "B", { "Off", "On" });
        }

        configLight(SCALE_A_LIGHT, "Scale A Selected");
        configLight(SCALE_B_LIGHT, "Scale B Selected");

        updateScaleLeds();
        
        initHistory();
        clockIntervalCounter = clockInterval = 0;
    }

    dsp::SchmittTrigger clockIn, resetIn, scaleSwitchTrig, scaleInputTrig;
    dsp::PulseGenerator clockOut, resetOut;

    int length, speedBPM, algoX, algoY, shift, space;

    int scales[SCALECOUNT][SCALELEN] = {};
    int scaleCount[SCALECOUNT] = {};
    int scale = 0;

    float internalClock = 2.f, speed, gateLen, transpose, clockInterval, clockIntervalCounter, gateLength, spread;
    int rotate = 0, globalCounter = 0, spaceCounter = 0;

    int counter[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int divisor[TRACKCOUNT] = { 2, 3, 5, 4, 7, 3, 5, 2 };
    int phase[TRACKCOUNT] = { 2, 3, 5, 4, 6, 7, 3, 2 };
    int weights[TRACKCOUNT] = { 1, 2, 4, 7, 5, 3, 4, 2 };
    int trackOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int weightOn[TRACKCOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int totalWeight = 0;

    int notes[NOTECOUNT][HISTORYCOUNT];
    bool gateOn[NOTECOUNT][HISTORYCOUNT];
    bool gateChanged[NOTECOUNT][HISTORYCOUNT];
    int shifts[NOTECOUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    float gateTimer[NOTECOUNT];
    bool gateTriggered[NOTECOUNT];

    int modCvs[MODCOUNT];
    bool modGateOn[MODCOUNT] = { 0, 0, 0, 0 };
    bool modGateChanged[MODCOUNT] = { 1, 1, 1, 1 };

    float getCombinedValue(int param, int input) {
        float min = paramQuantities[param]->minValue;
        float max = paramQuantities[param]->maxValue;
        float i = inputs[input].getVoltage() * (max - min) / 10.f + params[param].getValue();

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
        length = getCombinedValue(LENGTH_PARAM, LENGTH_INPUT);
        speedBPM = round(getCombinedValue(SPEED_PARAM, SPEED_INPUT));
        speed = 60.f / speedBPM;
        algoX = round(getCombinedValue(ALGO_X_PARAM, ALGO_X_INPUT));
        algoY = round(getCombinedValue(ALGO_Y_PARAM, ALGO_Y_INPUT));
        shift = round(getCombinedValue(SHIFT_PARAM, SHIFT_INPUT));
        space = round(getCombinedValue(SPACE_PARAM, SPACE_INPUT));
        transpose = getCombinedValue(TRANSPOSE_PARAM, TRANSPOSE_INPUT);
        gateLen = getCombinedValue(GATE_LEN_PARAM, GATE_LEN_INPUT);
        gateLength = speed * gateLen;
        spread = getCombinedValue(SPREAD_PARAM, SPREAD_INPUT);
    }

    void updateSyncedParameters() {
        rotate = round(getCombinedValue(ROTATE_PARAM, ROTATE_INPUT));
    }

    void updateTrackParameters() {
        divisor[0] = (algoX & 3) + 1;
        phase[0] = algoX >> 5;

        for (int i = 1; i < TRACKCOUNT; i++) {
            if (algoX & (1 << (i + 2))) divisor[i] = divisor[i - 1] + 1; else divisor[i] = divisor[i - 1] - 1;
            if (divisor[i] < 0) divisor[i] = 1 - divisor[i];
            if (divisor[i] == 0) divisor[i] = i + 2;
            phase[i] = ((algoX & (0b11 << i)) + i) % divisor[i];
        }

        for (int i = 0; i < TRACKCOUNT; i++) shifts[i] = getCombinedValue(SHIFT_PARAM, SHIFT_INPUT);
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
        modCvs[3] = weights[1] * (trackOn[1] + trackOn[2]) + weights[2] * (trackOn[2] + trackOn[3]) + weights[3] * (trackOn[3] + trackOn[2]);

        for (int i = 0; i < MODCOUNT; i++) modCvs[i] %= 10;
    }

    void initHistory() {
        for (uint8_t n = 0; n < NOTECOUNT; n++)
            for (uint8_t h = 1; h < HISTORYCOUNT; h++) {
                notes[n][h] = 0;
                gateOn[n][h] = 0;
                gateChanged[n][h] = 0;
            }
    }

    void pushHistory() {
        for (uint8_t n = 0; n < NOTECOUNT; n++)
            for (int8_t h = HISTORYCOUNT - 1; h > 0; h--) {
                notes[n][h] = notes[n][h-1];
                gateOn[n][h] = gateOn[n][h-1];
                gateChanged[n][h] = gateChanged[n][h-1];
            }
    }

    void calculateNote(int n) {
        int mask = algoY >> 3;

        notes[n][0] = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) notes[n][0] += weightOn[j];
        }

        if (algoY & 1) notes[n][0] += weightOn[(n + 1) % TRACKCOUNT];
        if (algoY & 2) notes[n][0] += weightOn[(n + 2) % TRACKCOUNT];
        if (algoY & 4) notes[n][0] += weightOn[(n + 3) % TRACKCOUNT];

        notes[n][0] += shifts[n];
    }

    void calculateNextNote(int n) {
        int mask = gatePresets[algoY >> 3][n];
        if (mask == 0) mask = 0b0101;
        for (int i = 0; i < n; i++) mask = ((mask & 1) << 3) | (mask >> 1);

        int g = 0;
        for (int j = 0; j < TRACKCOUNT; j++) {
            if (trackOn[j] && (mask & (1 << j))) g = 1;
            // if (mask & (1 << j)) g = 1;
        }

        if (algoY & 1) g ^= trackOn[n % TRACKCOUNT] << 1;
        if (algoY & 2) g ^= trackOn[(n + 2) % TRACKCOUNT] << 2;
        if (algoY & 4) g ^= trackOn[(n + 3) % TRACKCOUNT] << 3;

        bool previousGatesOn = 1;
        for (int i = 0; i < NOTECOUNT - 1; i++) previousGatesOn &= gateChanged[i][0] & gateOn[i][0];
        if (n == NOTECOUNT - 1 && previousGatesOn) g = 0;

        gateChanged[n][0] = gateOn[n][0] != g;
        gateOn[n][0] = g;
        if (gateChanged[n][0]) calculateNote(n);
    }
    

    void process(const ProcessArgs& args) override {
        bool advance = 0;
        if (inputs[CLOCK_INPUT].active) {
            advance = clockIn.process(rescale(inputs[CLOCK_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
        }
        else {
            internalClock += args.sampleTime;
            if (internalClock >= speed) {
                advance = 1;
                internalClock = 0;
            }
        }

        updateParameters();
        if (advance) updateSyncedParameters();
        processScaleSwitch();
        updateScales();

        if (advance) {
            updateCounters();
            updateMod();
            pushHistory();
            for (int n = 0; n < NOTECOUNT; n++) calculateNextNote(n);
            clockOut.trigger(1e-3);
            clockInterval = clockIntervalCounter;
            clockIntervalCounter = 0;
            for (int i = 0; i < NOTECOUNT; i++) gateTriggered[i] = false;
        } else {
            clockIntervalCounter += args.sampleTime;
        }

        float trans = transpose;
        if ((scale == 0 && getCombinedValue(SCALE_A_OCT_PARAM, SCALE_A_OCT_INPUT) > 0) || 
            (scale == 1 && getCombinedValue(SCALE_B_OCT_PARAM, SCALE_B_OCT_INPUT) > 0)) trans += 1.f;

        float cv, g;
        int cv_rotate = rotate > 0 ? rotate : 0;
        int g_rotate = rotate < 0 ? -rotate : 0;
        float delta;
        int history;
        
        for (int n = 0; n < NOTECOUNT; n++) {
            if (scaleCount[scale] == 0) {
                cv = scales[scale][0] / 12.f;
                g = 0;
            } else {
                delta = (spread > 0 ? spread * (float)n : -spread * (float)(NOTECOUNT - 1 - n)) / (float)NOTECOUNT;
                history = (int)delta;
                delta -= history;
                if (history >= HISTORYCOUNT) history = HISTORYCOUNT - 1;
                
                cv = scales[scale][notes[n][history] % scaleCount[scale]] / 12.f + std::min(2, notes[n][history] / 12) + trans;
                int sp = spacePresets[(space | n) % SPACEPRESETCOUNT];
                sp = 0;
                if (sp & spaceCounter) {
                    g = 0;
                } else {
                    if ((clockIntervalCounter >= (delta * clockInterval)) && !gateTriggered[n]) {
                        gateTriggered[n] = true;
                        gateTimer[n] = gateOn[n][history] ? gateLength : 0;
                    }
                    
                    if (gateTimer[n] > 0) gateTimer[n] -= args.sampleTime;
                    if (gateTimer[n] < 0) gateTimer[n] = 0;
                    g = gateTimer[n] > 0 ? 10 : 0;
                }
            }
            
            outputs[CV_1_OUTPUT + ((n + cv_rotate) % NOTECOUNT)].setVoltage(cv);
            outputs[GATE_1_OUTPUT + ((n + g_rotate) % NOTECOUNT)].setVoltage(g);
            
            outputs[CV_1_OUTPUT].setVoltage(cv, (n + cv_rotate) % NOTECOUNT);
            outputs[GATE_1_OUTPUT].setVoltage(g, (n + g_rotate) % NOTECOUNT);
        }

        outputs[CV_1_OUTPUT].setChannels(NOTECOUNT);
        outputs[GATE_1_OUTPUT].setChannels(NOTECOUNT);

        for (int i = 0; i < MODCOUNT; i++) {
            outputs[MOD_GATE_1_OUTPUT + i].setVoltage(modGateOn[i] ? 10.f : 0.f);
            outputs[MOD_CV_1_OUTPUT + i].setVoltage((float)(modCvs[i] % 8) / 7.f * 10.f);
        }

        outputs[CLOCK_OUTPUT].setVoltage(clockOut.process(args.sampleTime) ? 10.f : 0.f);
        outputs[RESET_OUTPUT].setVoltage(resetOut.process(args.sampleTime) ? 10.f : 0.f);
    }

    json_t* dataToJson() override {
        json_t* rootJ = json_object();
        json_object_set_new(rootJ, "selected_scale", json_integer(scale));
        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* scaleJ = json_object_get(rootJ, "selected_scale");
        if (scaleJ) {
            scale = json_integer_value(scaleJ);
            updateScaleLeds();
        }
    }
};

struct SDOrcasHeartWidget : ModuleWidget {
    SDOrcasHeartWidget(SDOrcasHeartV2* module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDOrcasHeartV2.svg")));

        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(52.661, 12.386)), module, SDOrcasHeartV2::SCALE_2_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(61.615, 12.386)), module, SDOrcasHeartV2::SCALE_4_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(79.522, 12.386)), module, SDOrcasHeartV2::SCALE_7_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(88.476, 12.386)), module, SDOrcasHeartV2::SCALE_9_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(97.429, 12.386)), module, SDOrcasHeartV2::SCALE_11_PARAM));
        addParam(createParamCentered<SDButton>(mm2px(Vec(113.681, 14.481)), module, SDOrcasHeartV2::SCALE_A_OCT_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(10.77, 14.492)), module, SDOrcasHeartV2::SCALE_A_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(141.63, 14.495)), module, SDOrcasHeartV2::SCALE_B_PARAM));
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
        addParam(createParamCentered<SDMomentaryButton>(mm2px(Vec(28.817, 14.481)), module, SDOrcasHeartV2::SCALE_PARAM));
        addParam(createParamCentered<SDButton>(mm2px(Vec(113.681, 30.264)), module, SDOrcasHeartV2::SCALE_B_OCT_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(47.655, 32.889)), module, SDOrcasHeartV2::SCALE_13_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(56.609, 32.889)), module, SDOrcasHeartV2::SCALE_15_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(65.562, 32.889)), module, SDOrcasHeartV2::SCALE_17_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(74.516, 32.889)), module, SDOrcasHeartV2::SCALE_18_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(83.47, 32.889)), module, SDOrcasHeartV2::SCALE_20_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(92.423, 32.889)), module, SDOrcasHeartV2::SCALE_22_PARAM));
        addParam(createParamCentered<SDScaleSwitch>(mm2px(Vec(101.377, 32.889)), module, SDOrcasHeartV2::SCALE_24_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(20.284, 50.164)), module, SDOrcasHeartV2::SPEED_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(42.651, 50.164)), module, SDOrcasHeartV2::ALGO_X_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(65.017, 50.164)), module, SDOrcasHeartV2::SHIFT_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(87.383, 50.164)), module, SDOrcasHeartV2::ROTATE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(109.749, 50.164)), module, SDOrcasHeartV2::XMOD_TYPE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(132.115, 50.164)), module, SDOrcasHeartV2::TRANSPOSE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(31.468, 67.91)), module, SDOrcasHeartV2::LENGTH_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(53.834, 67.91)), module, SDOrcasHeartV2::ALGO_Y_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(76.2, 67.91)), module, SDOrcasHeartV2::SPACE_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(98.566, 67.91)), module, SDOrcasHeartV2::SPREAD_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(120.932, 67.91)), module, SDOrcasHeartV2::XMOD_PARAM));
        addParam(createParamCentered<SDMediumKnob>(mm2px(Vec(143.299, 67.91)), module, SDOrcasHeartV2::GATE_LEN_PARAM));

        addInput(createInputCentered<SDPort>(mm2px(Vec(124.776, 14.481)), module, SDOrcasHeartV2::SCALE_A_OCT_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(28.817, 30.264)), module, SDOrcasHeartV2::SCALE_INPUT));
        addInput(createInputCentered<SDPort>(mm2px(Vec(10.77, 30.264)), module, SDOrcasHeartV2::SCALE_A_INPUT));
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
        addChild(createLightCentered<MediumLight<SDLight1>>(mm2px(Vec(41.298, 30.264)), module, SDOrcasHeartV2::SCALE_B_LIGHT));
    }
};

Model* modelSDOrcasHeartV2 = createModel<SDOrcasHeartV2, SDOrcasHeartWidget>("SDOrcasHeartV2");
