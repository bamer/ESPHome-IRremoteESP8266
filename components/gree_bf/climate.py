import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate_ir
from esphome.components import ir_remote_base
from esphome.const import CONF_MODEL

AUTO_LOAD = ["climate_ir", "ir_remote_base"]

gree_ns = cg.esphome_ns.namespace("gree")
GreeClimate = gree_ns.class_("GreeClimate", climate_ir.ClimateIR)

CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(GreeClimate)


Model = gree_ns.enum("Model")
MODELS = {
    "YAW1F": Model.YAW1F, # (1) Ultimate, EKOKAI, RusClimate (Default)
    "YBOFB": Model.YBOFB, #Green, YBOFB2, YAPOF3
    "YX1FSF": Model.YX1FSF # (3) Soleus Air window unit (Similar to YAW1F, but with an
                        #  Operation mode of Energy Saver (Econo))
}





CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(GreeClimate).extend(
    {
        cv.Required(CONF_MODEL): cv.enum(MODELS),
    }
)


async def to_code(config):
    ir_remote_base.load_ir_remote()

    var = await climate_ir.new_climate_ir(config)
    cg.add(var.setModel(config[CONF_MODEL]))