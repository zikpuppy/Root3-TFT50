#include "Home.h"
#include "includes.h"

const MENUITEMS homeItems = {
    // title
    LABEL_HOME,
// icon                          label

#ifdef CNC_MENU // if CNC menu is selected
    {
        {ICON_HOME, LABEL_XY},
        {ICON_Z_HOME, LABEL_Z},
        {ICON_NULL, LABEL_NULL},
        {ICON_PROBE_Z, LABEL_PROBE_Z},
        {ICON_ZERO_X, LABEL_ZERO_X},
        {ICON_ZERO_Y, LABEL_ZERO_Y},
        {ICON_ZERO_Z, LABEL_ZERO_Z},
        {ICON_BACK, LABEL_BACK},
    }
#else
    {
        {ICON_HOME, LABEL_HOME},
        {ICON_X_HOME, LABEL_X},
        {ICON_Y_HOME, LABEL_Y},
        {ICON_Z_HOME, LABEL_Z},
        {ICON_NULL, LABEL_NULL},
        {ICON_NULL, LABEL_NULL},
        {ICON_NULL, LABEL_NULL},
        {ICON_BACK, LABEL_BACK},
    }
#endif
};

void menuHome(void)
{
  KEY_VALUES key_num = KEY_IDLE;

  menuDrawPage(&homeItems);

  while (MENU_IS(menuHome))
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
#ifdef CNC_MENU // if CNC menu is selected
    case KEY_ICON_0:
      storeCmd("G28 XY\n");
      break;
    case KEY_ICON_1:
      storeCmd("G28 Z\n");
      break;
    case KEY_ICON_2:
      storeCmd("G92 X0 Y0 Z0\n");   // Set Coordinates to Zero
      storeCmd("G38.2 X-25 F50\n"); // Probe for X left 25mm until contact with probe face
      storeCmd("G92 X5.75\n");      // Set X Offset
      storeCmd("G0 X20 F200\n");    // Move X back to clear probe
      storeCmd("G38.2 Y-25 F50\n"); // Probe for Y forward 25mm until contact with probe face
      storeCmd("G92 Y7.21\n");      // Set Y Offset
      storeCmd("G0 Y20 F200\n");    // Move Y back to clear probe
      storeCmd("G0 Z15 F200\n");    // Lift Z before moving for next coordinate
      storeCmd("G0 X0 Y0\n");       // Go to XY zero coordinate
      storeCmd("G38.2 Z-15 F50\n"); // Probe Z down 15mm until contact with probe face
      storeCmd("G92 Z5.25\n");      // Set Z Offset
      storeCmd("G0 Z25 F200\n");
      break; // Lift Z before moving for next coordinate
    case KEY_ICON_3:
      storeCmd("G38.2 Z-30 F50\n");
      storeCmd("G92 Z8.15\n");
      storeCmd("G0 Z25 F200\n");
      break;
    case KEY_ICON_4:
      storeCmd("G92 X0\n");
      break;
    case KEY_ICON_5:
      storeCmd("G92 Y0\n");
      break;
    case KEY_ICON_6:
      storeCmd("G92 Z0\n");
      break;
#else
    case KEY_ICON_0:
      storeCmd("G28\n");
      break;
    case KEY_ICON_1:
      storeCmd("G28 X\n");
      break;
    case KEY_ICON_2:
      storeCmd("G28 Y\n");
      break;
    case KEY_ICON_3:
      storeCmd("G28 Z\n");
      break;
#endif
    case KEY_ICON_7:
      CLOSE_MENU();
      break;
    default:
      break;
    }

    loopProcess();
  }
}
