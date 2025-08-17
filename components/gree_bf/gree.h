#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/climate_ir/climate_ir.h"
#include <IRrecv.h>
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
            YAW1F = gree_ac_remote_model_t::YAW1F,
            YBOFB = gree_ac_remote_model_t::YBOFB,
            YX1FSF = gree_ac_remote_model_t::YX1FSF
              
        };

        
        class GreeClimate : public climate_ir::ClimateIR, public ir_remote_base::IrRemoteBase
        {
        public:
            GreeClimate()
                : ClimateIR(16, 30, 1.0f, true, true,
                            {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                            {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL, climate::CLIMATE_SWING_HORIZONTAL, climate::CLIMATE_SWING_BOTH}) {}

            void setup() override;
                climate::ClimateTraits traits() override;

            void step_horizontal();
            void step_vertical();
        protected:
            void transmit_state() override;

        private:
            void send();
            void apply_state();

            IRGreeAC ac_ = IRGreeAC(255); // pin is not used
            ///ac_.setLight= false;
        };

    } // namespace gree
} // namespace esphome

   
