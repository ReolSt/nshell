#ifndef AIRFORCE_CALL_H
#define AIRFORCE_CALL_H

#define AirForceCall(class, function, ...) ((class.function(&class, ## __VA_ARGS__)))
#define AirForceCallP(class, function, ...) ((class->function(class, ## __VA_ARGS__)))

#endif
