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

    int range = 0;
    float min[4] = {0, -10, 0, -5};
    float max[4] = {10, 10, 5, 5};
    bool bipolar[4] = {false, true, false, true};
    
    SDLines() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configInput(IN_INPUT, "Input");
    }
    
    json_t* dataToJson() override {
        json_t* rootJ = json_object();
        json_object_set_new(rootJ, "range", json_integer(range));
        return rootJ;
    }

    void dataFromJson(json_t* rootJ) override {
        json_t* rangeJ = json_object_get(rootJ, "range");
        if (rangeJ) range = json_integer_value(rangeJ);
    }
};

struct SDLinesDisplay : TransparentWidget {
    SDLines *module;
    NVGcolor pos = nvgRGB(255, 200, 0);
    NVGcolor neg = nvgRGB(255, 0, 0);
    float start, middle, height;
    
    SDLinesDisplay(Vec pos, Vec size) : TransparentWidget() {
        box.pos = pos;
        box.size = size;
        start = box.pos.y + box.size.y - 1.f;
        height = box.size.y - 2.f;
        middle = start - height / 2.f;
    }

    void drawLine(const DrawArgs &args, float x1, float y1, float x2, float y2, NVGcolor color) {
        nvgStrokeWidth(args.vg, 2.f);
        nvgStrokeColor(args.vg, color);
        nvgBeginPath(args.vg);
        nvgMoveTo(args.vg, x1, y1);
        nvgLineTo(args.vg, x2, y2);
        nvgStroke(args.vg);
    }
    
    void drawLayer(const DrawArgs &args,int layer) override {
        if (layer == 1) {
            nvgScissor(args.vg, box.pos.x, box.pos.y, box.size.x, box.size.y);

            if (module) {
                int channels = module->inputs[SDLines::IN_INPUT].getChannels();
                
                for (int i = 0; i < channels; i++) {
                    float voltage = module->inputs[SDLines::IN_INPUT].getVoltage(i) / (module->max[module->range] - module->min[module->range]);
                    if (voltage < module->min[module->range]) voltage = module->min[module->range];
                    else if (voltage > module->max[module->range]) voltage = module->max[module->range];
                    
                    float y = (module->bipolar[module->range] ? middle : start) - height * voltage;
                    drawLine(args, box.pos.x , y, box.pos.x + box.size.x, y, voltage >= 0 ? pos : neg);
                }
            }
        }
        
        Widget::drawLayer(args, layer);
    }
};

struct SDLinesWidget : ModuleWidget {
    SDLinesWidget(SDLines *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SDLines.svg")));

        addInput(createInputCentered<SDPort>(mm2px(Vec(5.08, 119.155)), module, SDLines::IN_INPUT));
        
        auto display = new SDLinesDisplay(mm2px(Vec(0.0, 5.463)), mm2px(Vec(10.16, 100.181)));
        display->module=module;
        addChild(display);    
    }
    
    void appendContextMenu(Menu* menu) override {
        SDLines* module = getModule<SDLines>();
        menu->addChild(new MenuSeparator);
        menu->addChild(createIndexPtrSubmenuItem("Range", {"0 .. +10", "-10 .. +10", "0 .. +5", "-5 .. +5"}, &module->range));
    }
};

Model *modelSDLines = createModel<SDLines, SDLinesWidget>("SDLines");