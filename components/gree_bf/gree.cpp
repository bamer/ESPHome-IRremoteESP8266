#define _IR_ENABLE_DEFAULT_ false
#define SEND_GREE_AC true
#define DECODE_GREE_AC false

#include "esphome.h"
#include "ir_Gree.h"
#include "gree.h"

namespace esphome
{
    namespace gree
    {
        // copied from ir_Gree.cpp
        const uint16_t kGreeHdrMark = 9000;
        const uint16_t kGreeHdrSpace = 4500;  ///< See #684 & real example in unit tests
        const uint16_t kGreeBitMark = 620;
        const uint16_t kGreeOneSpace = 1600;
        const uint16_t kGreeZeroSpace = 540;
        const uint16_t kGreeMsgSpace = 19980;  ///< See #1508, #386, & Kelvinator
        const uint8_t kGreeBlockFooter = 0b010;
        const uint8_t kGreeBlockFooterBits = 3;
        const uint32_t kGreeMessageGap = kDefaultMessageGap;  // Just a guess.

        static const char *const TAG = "gree.climate";

        void GreeClimate::setup()
        {
            climate_ir::ClimateIR::setup();
            this->apply_state();
        }

        void GreeClimate::transmit_state()
        {
            this->apply_state();
            this->send();
        }

        void GreeClimate::send()
        {
            uint8_t *message = this->ac_.getRaw();

            sendGeneric(
                this->transmitter_,
                kGreeHdrMark, kGreeHdrSpace,
                kGreeBitMark, kGreeOneSpace,
                kGreeBitMark, kGreeZeroSpace,
                kGreeBitMark, kGreeMessageGap,
                message, kGreeStateLength,
                38000
            );
        }

        void GreeClimate::apply_state()
        {
            if (this->mode == climate::CLIMATE_MODE_OFF)
            {
                this->ac_.off();
            }
            else
            {
                this->ac_.setTemp(this->target_temperature);

                switch (this->mode)
                {
                case climate::CLIMATE_MODE_AUTO:
                    this->ac_.setMode(kGreeFanAuto);
                    break;
                case climate::CLIMATE_MODE_HEAT:
                    this->ac_.setMode(kGreeHeat);
                    break;
                case climate::CLIMATE_MODE_COOL:
                    this->ac_.setMode(kGreeCool);
                    break;
                case climate::CLIMATE_MODE_DRY:
                    this->ac_.setMode(kGreeDry);
                    break;
                case climate::CLIMATE_MODE_FAN_ONLY:
                    this->ac_.setMode(kGreeFan);
                    break;
                }

                if (this->fan_mode.has_value())
                {
                    switch (this->fan_mode.value())
                    {
                    case climate::CLIMATE_FAN_AUTO:
                        this->ac_.setFan(kGreeFanAuto);
                        break;
                    case climate::CLIMATE_FAN_LOW:
                        this->ac_.setFan(kGreeFanMin);
                        break;
                    case climate::CLIMATE_FAN_MEDIUM:
                        this->ac_.setFan(kGreeFanMed);
                        break;
                    case climate::CLIMATE_FAN_HIGH:
                        this->ac_.setFan(kGreeFanMax);
                        break;
                    }
                }

                switch (this->swing_mode)
                {
                case climate::CLIMATE_SWING_OFF:
                    this->ac_.setSwingHorizontal(kGreeSwingHOff);
                    this->ac_.setSwingVertical(kGreeSwingHOff);
                    break;
                case climate::CLIMATE_SWING_VERTICAL:
                    this->ac_.setSwingHorizontal(kGreeSwingHOff);
                    this->ac_.setSwingVertical(kGreeSwingAuto);
                    break;
                case climate::CLIMATE_SWING_HORIZONTAL:
                    this->ac_.setSwingHorizontal(kGreeSwingAuto);
                    this->ac_.setSwingVertical(kGreeSwingHOff);
                    break;
                case climate::CLIMATE_SWING_BOTH:
                    this->ac_.setSwingHorizontal(kGreeSwingAuto);
                    this->ac_.setSwingVertical(kGreeSwingAuto);
                    break;
                }

                this->ac_.on();
            }

            ESP_LOGI(TAG, "%s", this->ac_.toString().c_str());
        }
    } // namespace gree
} // namespace esphome
