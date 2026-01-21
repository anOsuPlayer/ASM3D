#include <stdio.h>

#include "window.h"
#include "render.h"

#include <sys/ioctl.h>
#include <unistd.h>

int main() {

    get_screen_size();

    printf("%d", screen_w);
}