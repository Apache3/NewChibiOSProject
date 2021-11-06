#include <ch.hpp>
#include <hal.h>
#include <shell.h>
#include "ProjectShell.hpp"
#include <Logging.hpp>
#include "BuildConf.hpp"

static THD_WORKING_AREA(waShellThread, SHELL_WA_SIZE);

int main() {
    halInit();
    chSysInit();

    Logging::init();
    Logging::println("[main] Starting up");
    shellInit();

    chThdCreateStatic(waShellThread, sizeof(waShellThread), NORMALPRIO,
                      shellThread, (void*)&shell_cfg);
    palSetLineMode(LED_LINE, LED_LINE_MODE);
    while (!chThdShouldTerminateX()) {
        palToggleLine(LED_LINE);
        chThdSleepMilliseconds(1000);
    }

    Logging::println("[main] Shutting down");
}
