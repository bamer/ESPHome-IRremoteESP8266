#pragma once

#include "esphome/esphome/core/log.h"
#include "esphome/esphome/core/component.h"
#include "esphome/esphome/core/automation.h"
#include "esphome/esphome/components/climate_ir/climate_ir.h"

#include "ir_Gree.h"
#include "esphome/components/ir_remote_base/ir_remote_base.h"


// Supports:
//   Brand: Ultimate,  Model: Heat Pump
//   Brand: EKOKAI,  Model: A/C
//   Brand: RusClimate,  Model: EACS/I-09HAR_X/N3 A/C
//   Brand: RusClimate,  Model: YAW1F remote
//   Brand: Green,  Model: YBOFB remote
//   Brand: Green,  Model: YBOFB2 remote
//   Brand: Gree,  Model: YAA1FBF remote
//   Brand: Gree,  Model: YB1F2F remote
//   Brand: Gree,  Model: YAN1F1 remote
//   Brand: Gree,  Model: YX1F2F remote (YX1FSF)
//   Brand: Gree,  Model: VIR09HP115V1AH A/C
//   Brand: Gree,  Model: VIR12HP230V1AH A/C
//   Brand: Amana,  Model: PBC093G00CC A/C
//   Brand: Amana,  Model: YX1FF remote
//   Brand: Cooper & Hunter,  Model: YB1F2 remote
//   Brand: Cooper & Hunter,  Model: CH-S09FTXG A/C
//   Brand: Vailland,  Model: YACIFB remote
//   Brand: Vailland,  Model: VAI5-035WNI A/C
//   Brand: Soleus Air,  Model: window A/C (YX1FSF)


namespace esphome
{
    namespace gree
    {
        enum Model {
            YBOFB2 = gree_ac_remote_model_t::YBOFB,
            YBOFB2 = gree_ac_remote_model_t::YBOFB2,
            YAA1FBF = gree_ac_remote_model_t::YAA1FBF,
            YB1F2F = gree_ac_remote_model_t::YB1F2F,
            YAN1F1 = gree_ac_remote_model_t::YAN1F1,
            YX1F2F = gree_ac_remote_model_t::YX1F2F,
            VIR09HP115V1AH = gree_ac_remote_model_t::VIR09HP115V1AH,
            VIR12HP230V1AH = gree_ac_remote_model_t::VIR12HP230V1AH,
            YX1FF = gree_ac_remote_model_t::YX1FF,
            YACIFB = gree_ac_remote_model_t::YACIFB  
        };

        class GreeClimate : public climate_ir::ClimateIR, public ir_remote_base::IrRemoteBase
        {
        public:
            GreeClimate()
                : ClimateIR(16, 30, 1.0f, true, true,
                            {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                            {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL, climate::CLIMATE_SWING_HORIZONTAL, climate::CLIMATE_SWING_BOTH}) {}

            void setup() override;

        protected:
            void transmit_state() override;

        private:
            void send();
            void apply_state();

            IRGreeAc ac_ = IRGreeAc(255); // pin is not used
            ac_.setLight= false;
        };

    } // namespace gree
} // namespace esphome
