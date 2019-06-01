#ifndef HANZO_CALL_H
#define HANZO_CALL_H
#define HanzoCall(class, function, ...) (class.function(&class, __VA_ARGS__))
#define HanzoCallP(class, function, ...) (class->function(class, __VA_ARGS__))
#endif
