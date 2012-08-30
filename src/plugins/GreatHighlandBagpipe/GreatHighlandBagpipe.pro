include(../../../LimePipes.pri)
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include(GreatHighlandBagpipe.pri)

TEMPLATE      = lib
CONFIG       += plugin static
TARGET        = lp_greathighlandbagpipe
DESTDIR       = $$LIMEPIPES_STATIC_PLUGINS_FOLDER

