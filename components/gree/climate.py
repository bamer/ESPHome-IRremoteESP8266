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
    "YBOFB2": Model.YBOFB2,
    "YAA1FBF": Model.YAA1FBF,
    "YB1F2F": Model.YB1F2F,
    "YAN1F1": Model.YAN1F1,
    "YX1F2F": Model.YX1F2F,
    "VIR09HP115V1AH": Model.VIR09HP115V1AH,
    "VIR12HP230V1AH": Model.VIR12HP230V1AH,
    "YX1FF": Model.YX1FF,
    "yac1fb9": Model.YAC1FB9,    
    "YACIFB": Model.YACIFB

}

           
    




CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(GreeClimate).extend(
    {
        cv.Required(CONF_MODEL): cv.enum(MODELS),
    }
)


async def to_code(config):
    ir_remote_base.load_ir_remote()

    var = await climate_ir.new_climate_ir(config)
    cg.add(var.set_model(config[CONF_MODEL]))