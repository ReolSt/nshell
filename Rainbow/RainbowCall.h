#ifndef RAINBOW_CALL_H
#define RAINBOW_CALL_H

#define RainbowCall(class, function, ...) ((class.function(&class, ## __VA_ARGS__)))
#define RainbowCallP(class, function, ...) ((class->function(class, ## __VA_ARGS__)))

#endif
