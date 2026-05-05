#include "camera.h"
#include "controls.h"

static Camera*          CAMERAS;
static UINT             CCOUNT;

void InitializeCameras() {
    CAMERAS = (Camera*) malloc(sizeof(Camera));

    CCURRENT = MakeCamera();

    CCURRENT->TRANSFORM->pos.x = 1;
    CCURRENT->TRANSFORM->pos.y = 1;
    CCURRENT->TRANSFORM->pos.z = 1;

    CCURRENT->TRANSFORM->angle.x = 0;
    CCURRENT->TRANSFORM->angle.y = 0;
    CCURRENT->TRANSFORM->angle.z = 0;

    strcpy(CCURRENT->name, "DEFAULT");
}

void TerminateCameras() {
    for (UINT i = 0; i < CCOUNT; i++) {
        FreeCamera(CAMERAS[i]);
    }
    free(CAMERAS);
}

Camera MakeCamera() {
    Camera c = (Camera) malloc(sizeof(struct camera_t));

    c->QUATERNION = make_vec();
    c->VIEW = make_matrix();
    c->PERSPECTIVE = make_matrix();

    c->TRANSFORM = (Transform) malloc(sizeof(struct transform_t));

    c->FOV = 65.0f;

    c->Near = 0.01f;
    c->Far = 500.0f;

    CAMERAS = (Camera*) realloc(CAMERAS, (++CCOUNT) * sizeof(Camera));
    CAMERAS[CCOUNT-1] = c;
}

void FreeCamera(Camera c) {
    free_vec(c->QUATERNION);
    free_matrix(c->VIEW);
    free_matrix(c->PERSPECTIVE);

    free(c->TRANSFORM);

    free(c);
}

static Camera           CUPDATED;
static BOOL             CUPDATE_TRIGGER = FALSE;

void SwitchCamera(const char* to) {
    for (UINT i = 0; i < CCOUNT; i++) {
        if (strcmp(to, CAMERAS[i]->name) == 0) {
            CUPDATED = CAMERAS[i];
            CUPDATE_TRIGGER = TRUE;
            break;
        }
    }
}

void ConfirmCameraSwitch() {
    if (CUPDATE_TRIGGER) {
        CCURRENT = CUPDATED;
        CUPDATE_TRIGGER = FALSE;
    }
}

void DeleteCamera(const char* c) {
    Camera d;

    for (UINT i = 0; i < CCOUNT; i++) {
        if (strcmp(c, CAMERAS[i]->name) == 0) {
            d = CAMERAS[i];
            CAMERAS[i] = CAMERAS[--CCOUNT];
            break;
        }
    }

    if (d != NULL) {
        if (CCURRENT == d) {
            CCURRENT = (CCOUNT == 0) ? NULL : CAMERAS[0];
        }
        FreeCamera(d);
        CAMERAS = realloc(CAMERAS, CCOUNT * sizeof(Camera));
    }
}

void DisplayData(HWND hwnd, HDC hdc, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetTextColor(hdc, GetFontFG());
    SetBkColor(hdc, GetFontBG());
    SelectObject(hdc, DEFAULT_FONT());

    Camera c = CCURRENT;
    
    CHAR str1[200];
    CHAR str2[500];
    
    RECT rec;
    GetClientRect(hwnd, &rec);
    rec.top += 20;
    rec.left += 20;
    rec.bottom -= 20;
    rec.right -= 20;
    
    if (c != NULL) {
        sprintf(str1, "x: %+.3f, y: %+.3f, z: %+.3f\nyaw: %+.3f, pitch: %+.3f, roll: %+.3f\nFOV: %.1f, AR: %.4f\nMovement: %s",
            c->TRANSFORM->pos.x, c->TRANSFORM->pos.y, c->TRANSFORM->pos.z,
            c->TRANSFORM->angle.x, c->TRANSFORM->angle.y, c->TRANSFORM->angle.z,
            c->FOV, AR,
            (IsDirectional() ? "Directional" : "Absolute"));
        
        DrawText(hdc, str1, -1, &rec, DT_CENTER);

        sprintf(str2, "Camera : \"%s\"\n\n"
            "QUATERNION :\n%+.3f %+.3f %+.3f %+.3f\n" \
            "VIEW :\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f\n" \
            "PERSPECTIVE :\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f\n%+.2f %+.2f %+.2f %+.2f",
            (CCURRENT == NULL) ? "None" : CCURRENT->name, 
            c->QUATERNION->x, c->QUATERNION->y, c->QUATERNION->z, c->QUATERNION->w,
            c->VIEW->r0.x, c->VIEW->r0.y, c->VIEW->r0.z, c->VIEW->r0.w, 
            c->VIEW->r1.x, c->VIEW->r1.y, c->VIEW->r1.z, c->VIEW->r1.w, 
            c->VIEW->r2.x, c->VIEW->r2.y, c->VIEW->r2.z, c->VIEW->r2.w, 
            c->VIEW->r3.x, c->VIEW->r3.y, c->VIEW->r3.z, c->VIEW->r3.w,
            c->PERSPECTIVE->r0.x, c->PERSPECTIVE->r0.y, c->PERSPECTIVE->r0.z, c->PERSPECTIVE->r0.w,
            c->PERSPECTIVE->r1.x, c->PERSPECTIVE->r1.y, c->PERSPECTIVE->r1.z, c->PERSPECTIVE->r1.w,
            c->PERSPECTIVE->r2.x, c->PERSPECTIVE->r2.y, c->PERSPECTIVE->r2.z, c->PERSPECTIVE->r2.w,
            c->PERSPECTIVE->r3.x, c->PERSPECTIVE->r3.y, c->PERSPECTIVE->r3.z, c->PERSPECTIVE->r3.w 
        );

        DrawText(hdc, str2, -1, &rec, DT_LEFT);
    }
    
    CHAR str3[500];
    sprintf(str3, "frametime: %9lluns\nFPS: %11.2f\n\nHighest: %11.2f\nLowest: %11.2f", GetFrameTime(), 1e9f / GetFrameTime(),
        1e9f / GetLowestFrameTime(), 1e9f / GetHighestFrameTime());

    DrawText(hdc, str3, -1, &rec, DT_RIGHT);
}