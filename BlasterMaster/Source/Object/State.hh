#pragma once

#define SD_IS_UP(s)     ((s & 0x1) == 0)
#define SD_IS_DOWN(s)   ((s & 0x1) != 0)
#define SD_IS_LEFT(s)   ((s & 0x2) == 0)
#define SD_IS_RIGHT(s)  ((s & 0x2) != 0)

#define SM_IS_IDLE(s)   ((s & 0x4) == 0)
#define SM_IS_WALK(s)   ((s & 0x4) != 0)
#define SM_IS_FALL(s)   ((s & 0x8) == 0)
#define SM_IS_JUMP(s)   ((s & 0x8) != 0)

#define SD_SET_UP(s)    s = (s & (~(1 << 0)))
#define SD_SET_DOWN(s)  s = (s |   (1 << 0))
#define SD_SET_LEFT(s)  s = (s & (~(1 << 1)))
#define SD_SET_RIGHT(s) s = (s |   (1 << 1))

#define SM_SET_IDLE(s)  s = (s & (~(1 << 2)))
#define SM_SET_WALK(s)  s = (s |   (1 << 2))
#define SM_SET_FALL(s)  s = (s & (~(1 << 3)))
#define SM_SET_JUMP(s)  s = (s |   (1 << 3))
