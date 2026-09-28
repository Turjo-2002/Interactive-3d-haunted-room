#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359f

/* ============================================================
   CAMERA
   ============================================================ */

float cameraX = 0.0f;
float cameraY = 1.7f;
float cameraZ = 5.0f;

float cameraYaw = 0.0f;
float cameraPitch = 0.0f;

float moveSpeed = 0.20f;

/* ============================================================
   GLOBAL TIME
   ============================================================ */

float gameTime = 0.0f;

/* ============================================================
   DOOR
   ============================================================ */

float doorAngle = 0.0f;

int doorMoving = 0;
int doorOpening = 1;
int hauntedDoor = 0;
int doorSlamming = 0;

/* ============================================================
   LIGHTING
   ============================================================ */

int mainLightOn = 1;
int candleOn = 1;
int moonLightOn = 1;

int ghostDarkMode = 0;

int flickering = 0;
float flickerStartTime = 0.0f;

int blackout = 0;
int redLight = 0;

int lightningActive = 0;
float lightningStartTime = 0.0f;

/* Candle flame scale */
float candleFlameScale = 1.0f;

/* ============================================================
   FAN
   ============================================================ */

float fanAngle = 0.0f;
float fanSpeed = 2.0f;
int fanMode = 1;

/* ============================================================
   GHOST
   ============================================================ */

int ghostActive = 0;
int ghostFollowMode = 0;
int ghostEmerging = 0;

float ghostAlpha = 0.0f;
float ghostScale = 0.1f;

float ghostX = -3.1f;
float ghostY = 3.2f;
float ghostZ = -6.5f;

float ghostTargetX = -2.2f;
float ghostTargetY = 2.7f;
float ghostTargetZ = -5.1f;

/* ============================================================
   PERSON
   ============================================================ */

int personVisible = 1;

int personTurning = 0;
int personCreepyMode = 0;

int personScared = 0;
int personRunning = 0;
int personEscaped = 0;

float personHeadAngle = 0.0f;
float personBodyAngle = 180.0f;

float personX = -1.6f;
float personZ = -5.8f;

float personReactionStartTime = 0.0f;

/* ============================================================
   CHAIR
   ============================================================ */

int chairMoving = 0;

float chairOffsetX = 0.0f;
float chairOffsetZ = 0.0f;

/* ============================================================
   PAINTING
   ============================================================ */

int paintingHaunted = 0;

/* ============================================================
   LEVITATION
   ============================================================ */

int levitationActive = 0;

/* ============================================================
   CUPBOARD
   ============================================================ */

int cupboardOpening = 0;
float cupboardDoorAngle = 0.0f;

/* ============================================================
   BED
   ============================================================ */

int bedShaking = 0;

/* ============================================================
   CURTAINS
   ============================================================ */

int curtainsMoving = 1;

/* ============================================================
   CLOCK
   ============================================================ */

int clockHaunted = 0;

float clockMinuteAngle = 0.0f;
float clockHourAngle = 0.0f;

/* ============================================================
   BOOKS
   ============================================================ */

int booksHaunted = 0;

/* ============================================================
   FOG
   ============================================================ */

int fogEnabled = 1;

/* ============================================================
   FULL HAUNTING SEQUENCE
   ============================================================ */

int paranormalSequence = 0;

float sequenceStartTime = 0.0f;
int sequenceStage = 0;

/* ============================================================
   SUDDEN HORROR INCIDENT
   ============================================================ */

int horrorIncident = 0;

float horrorStartTime = 0.0f;
int horrorStage = 0;

/* ============================================================
   FUNCTION PROTOTYPES
   ============================================================ */

void setMaterial(
    float r,
    float g,
    float b,
    float alpha,
    float shininess
);

void drawCube(
    float x,
    float y,
    float z,
    float sx,
    float sy,
    float sz,
    float r,
    float g,
    float b
);

void drawRoom(void);
void drawBed(void);
void drawTable(void);
void drawChair(void);
void drawWindow(void);
void drawPerson(void);
void drawPainting(void);
void drawCupboard(void);
void drawClock(void);
void drawDoor(void);
void drawFan(void);
void drawCandle(void);
void drawSkull(void);
void drawBooks(void);
void drawGhost(void);

void setupLighting(void);
void setupCamera(void);

int validPosition(
    float x,
    float z
);

void triggerDoor(void);
void triggerFlicker(void);
void triggerLightning(void);

void startGhostWindowEvent(void);

void resetHaunting(void);

void updateParanormalSequence(void);
void updateHorrorIncident(void);

void update(int value);

void drawText(
    float x,
    float y,
    const char *text
);

void drawHUD(void);

void display(void);

void keyboard(
    unsigned char key,
    int x,
    int y
);

void specialKeys(
    int key,
    int x,
    int y
);

void reshape(
    int width,
    int height
);

void init(void);

/* ============================================================
   MATERIAL
   ============================================================ */

void setMaterial(
    float r,
    float g,
    float b,
    float alpha,
    float shininess
)
{
    GLfloat ambient[] =
    {
        r * 0.25f,
        g * 0.25f,
        b * 0.25f,
        alpha
    };

    GLfloat diffuse[] =
    {
        r,
        g,
        b,
        alpha
    };

    GLfloat specular[] =
    {
        0.35f,
        0.35f,
        0.35f,
        alpha
    };

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_AMBIENT,
        ambient
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_DIFFUSE,
        diffuse
    );

    glMaterialfv(
        GL_FRONT_AND_BACK,
        GL_SPECULAR,
        specular
    );

    glMaterialf(
        GL_FRONT_AND_BACK,
        GL_SHININESS,
        shininess
    );
}

/* ============================================================
   BASIC CUBE
   ============================================================ */

void drawCube(
    float x,
    float y,
    float z,

    float sx,
    float sy,
    float sz,

    float r,
    float g,
    float b
)
{
    glPushMatrix();

    glTranslatef(
        x,
        y,
        z
    );

    glScalef(
        sx,
        sy,
        sz
    );

    setMaterial(
        r,
        g,
        b,
        1.0f,
        20.0f
    );

    glutSolidCube(
        1.0f
    );

    glPopMatrix();
}

/* ============================================================
   ROOM
   ============================================================ */

void drawRoom(void)
{
    /* Floor */

    drawCube(
        0.0f,
        -0.1f,
        0.0f,

        12.0f,
        0.2f,
        14.0f,

        0.22f,
        0.10f,
        0.04f
    );

    /* Ceiling */

    drawCube(
        0.0f,
        6.0f,
        0.0f,

        12.0f,
        0.2f,
        14.0f,

        0.12f,
        0.12f,
        0.14f
    );

    /* Left wall */

    drawCube(
        -6.0f,
        3.0f,
        0.0f,

        0.2f,
        6.0f,
        14.0f,

        0.20f,
        0.21f,
        0.22f
    );

    /* Right wall */

    drawCube(
        6.0f,
        3.0f,
        0.0f,

        0.2f,
        6.0f,
        14.0f,

        0.20f,
        0.21f,
        0.22f
    );

    /* Back wall */

    drawCube(
        0.0f,
        3.0f,
        -7.0f,

        12.0f,
        6.0f,
        0.2f,

        0.18f,
        0.19f,
        0.20f
    );

    /* Front left */

    drawCube(
        -4.0f,
        3.0f,
        7.0f,

        4.0f,
        6.0f,
        0.2f,

        0.18f,
        0.19f,
        0.20f
    );

    /* Front right */

    drawCube(
        4.0f,
        3.0f,
        7.0f,

        4.0f,
        6.0f,
        0.2f,

        0.18f,
        0.19f,
        0.20f
    );

    /* Wall above door */

    drawCube(
        0.0f,
        5.2f,
        7.0f,

        4.0f,
        1.6f,
        0.2f,

        0.18f,
        0.19f,
        0.20f
    );
}

/* ============================================================
   BED
   ============================================================ */

void drawBed(void)
{
    float shake = 0.0f;

    glPushMatrix();

    if(bedShaking)
    {
        shake =
            0.04f *
            sinf(
                gameTime *
                35.0f
            );
    }

    glTranslatef(
        shake,
        0.0f,
        0.0f
    );

    /* frame */

    drawCube(
        -3.7f,
        0.35f,
        -2.3f,

        3.5f,
        0.5f,
        5.0f,

        0.28f,
        0.09f,
        0.03f
    );

    /* mattress */

    drawCube(
        -3.7f,
        0.75f,
        -2.3f,

        3.3f,
        0.4f,
        4.7f,

        0.45f,
        0.38f,
        0.32f
    );

    /* headboard */

    drawCube(
        -3.7f,
        1.5f,
        -4.75f,

        3.5f,
        2.4f,
        0.3f,

        0.20f,
        0.06f,
        0.02f
    );

    /* pillows */

    drawCube(
        -4.3f,
        1.05f,
        -3.9f,

        1.1f,
        0.3f,
        0.8f,

        0.55f,
        0.52f,
        0.45f
    );

    drawCube(
        -3.0f,
        1.05f,
        -3.9f,

        1.1f,
        0.3f,
        0.8f,

        0.55f,
        0.52f,
        0.45f
    );

    glPopMatrix();
}

/* ============================================================
   TABLE
   ============================================================ */

void drawTable(void)
{
    float x = 2.7f;
    float z = -2.5f;

    /* top */

    drawCube(
        x,
        1.5f,
        z,

        3.0f,
        0.25f,
        2.0f,

        0.30f,
        0.10f,
        0.03f
    );

    /* legs */

    drawCube(
        x - 1.2f,
        0.75f,
        z - 0.7f,

        0.2f,
        1.5f,
        0.2f,

        0.23f,
        0.07f,
        0.02f
    );

    drawCube(
        x + 1.2f,
        0.75f,
        z - 0.7f,

        0.2f,
        1.5f,
        0.2f,

        0.23f,
        0.07f,
        0.02f
    );

    drawCube(
        x - 1.2f,
        0.75f,
        z + 0.7f,

        0.2f,
        1.5f,
        0.2f,

        0.23f,
        0.07f,
        0.02f
    );

    drawCube(
        x + 1.2f,
        0.75f,
        z + 0.7f,

        0.2f,
        1.5f,
        0.2f,

        0.23f,
        0.07f,
        0.02f
    );
}

/* ============================================================
   CHAIR
   ============================================================ */

void drawChair(void)
{
    float extraRotation =
        0.0f;

    glPushMatrix();

    if(chairMoving)
    {
        extraRotation =
            15.0f *
            sinf(
                gameTime *
                1.2f
            );
    }

    glTranslatef(
        3.5f +
        chairOffsetX,

        0.0f,

        0.8f +
        chairOffsetZ
    );

    glRotatef(
        -25.0f +
        extraRotation,

        0.0f,
        1.0f,
        0.0f
    );

    /* seat */

    drawCube(
        0.0f,
        1.0f,
        0.0f,

        1.5f,
        0.25f,
        1.5f,

        0.27f,
        0.08f,
        0.02f
    );

    /* back */

    drawCube(
        0.0f,
        2.0f,
        0.65f,

        1.5f,
        2.0f,
        0.2f,

        0.27f,
        0.08f,
        0.02f
    );

    /* legs */

    drawCube(
        -0.55f,
        0.5f,
        -0.55f,

        0.15f,
        1.0f,
        0.15f,

        0.20f,
        0.05f,
        0.01f
    );

    drawCube(
        0.55f,
        0.5f,
        -0.55f,

        0.15f,
        1.0f,
        0.15f,

        0.20f,
        0.05f,
        0.01f
    );

    drawCube(
        -0.55f,
        0.5f,
        0.55f,

        0.15f,
        1.0f,
        0.15f,

        0.20f,
        0.05f,
        0.01f
    );

    drawCube(
        0.55f,
        0.5f,
        0.55f,

        0.15f,
        1.0f,
        0.15f,

        0.20f,
        0.05f,
        0.01f
    );

    glPopMatrix();
}

/* ============================================================
   WINDOW + NIGHT
   ============================================================ */

void drawWindow(void)
{
    float curtainSwing =
        0.0f;

    if(curtainsMoving)
    {
        curtainSwing =
            4.0f *
            sinf(
                gameTime *
                1.2f
            );
    }

    glPushMatrix();

    glTranslatef(
        -3.1f,
        3.5f,
        -6.82f
    );

    /* night sky */

    glDisable(
        GL_LIGHTING
    );

    glColor3f(
        0.015f,
        0.02f,
        0.08f
    );

    glBegin(
        GL_QUADS
    );

    glVertex3f(
        -1.5f,
        -1.4f,
        0.02f
    );

    glVertex3f(
        1.5f,
        -1.4f,
        0.02f
    );

    glVertex3f(
        1.5f,
        1.4f,
        0.02f
    );

    glVertex3f(
        -1.5f,
        1.4f,
        0.02f
    );

    glEnd();

    /* stars */

    glPointSize(
        3.0f
    );

    glColor3f(
        0.8f,
        0.85f,
        1.0f
    );

    glBegin(
        GL_POINTS
    );

    glVertex3f(-1.0f, 0.8f, 0.06f);
    glVertex3f(-0.6f, 1.0f, 0.06f);
    glVertex3f(0.4f, 0.9f, 0.06f);
    glVertex3f(1.0f, 0.4f, 0.06f);
    glVertex3f(-0.2f, 0.2f, 0.06f);
    glVertex3f(0.8f, -0.6f, 0.06f);
    glVertex3f(-1.2f, -0.4f, 0.06f);

    glEnd();

    glEnable(
        GL_LIGHTING
    );

    /* moon */

    glPushMatrix();

    glTranslatef(
        0.65f,
        0.65f,
        0.12f
    );

    setMaterial(
        0.75f,
        0.78f,
        0.65f,
        1.0f,
        20.0f
    );

    glutSolidSphere(
        0.35,
        25,
        25
    );

    glPopMatrix();

    /* outer frame */

    drawCube(
        0.0f,
        1.45f,
        0.15f,

        3.4f,
        0.15f,
        0.15f,

        0.16f,
        0.07f,
        0.02f
    );

    drawCube(
        0.0f,
        -1.45f,
        0.15f,

        3.4f,
        0.15f,
        0.15f,

        0.16f,
        0.07f,
        0.02f
    );

    drawCube(
        -1.55f,
        0.0f,
        0.15f,

        0.15f,
        3.0f,
        0.15f,

        0.16f,
        0.07f,
        0.02f
    );

    drawCube(
        1.55f,
        0.0f,
        0.15f,

        0.15f,
        3.0f,
        0.15f,

        0.16f,
        0.07f,
        0.02f
    );

    /* cross */

    drawCube(
        0.0f,
        0.0f,
        0.17f,

        0.10f,
        2.8f,
        0.12f,

        0.16f,
        0.07f,
        0.02f
    );

    drawCube(
        0.0f,
        0.0f,
        0.17f,

        3.0f,
        0.10f,
        0.12f,

        0.16f,
        0.07f,
        0.02f
    );

    /* left curtain */

    glPushMatrix();

    glTranslatef(
        -1.8f,
        0.0f,
        0.35f
    );

    glRotatef(
        curtainSwing,
        0.0f,
        0.0f,
        1.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.55f,
        3.5f,
        0.15f,

        0.25f,
        0.02f,
        0.04f
    );

    glPopMatrix();

    /* right curtain */

    glPushMatrix();

    glTranslatef(
        1.8f,
        0.0f,
        0.35f
    );

    glRotatef(
        -curtainSwing,
        0.0f,
        0.0f,
        1.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.55f,
        3.5f,
        0.15f,

        0.25f,
        0.02f,
        0.04f
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   PERSON
   ============================================================ */

void drawPerson(void)
{
    float legSwing =
        0.0f;

    float armSwing =
        0.0f;

    if(!personVisible)
    {
        return;
    }

    if(personRunning)
    {
        legSwing =
            28.0f *
            sinf(
                gameTime *
                18.0f
            );

        armSwing =
            -legSwing;
    }

    glPushMatrix();

    glTranslatef(
        personX,
        0.0f,
        personZ
    );

    glRotatef(
        personBodyAngle,
        0.0f,
        1.0f,
        0.0f
    );

    /* torso */

    glPushMatrix();

    glTranslatef(
        0.0f,
        1.85f,
        0.0f
    );

    glScalef(
        0.85f,
        1.45f,
        0.45f
    );

    setMaterial(
        0.03f,
        0.03f,
        0.04f,
        1.0f,
        10.0f
    );

    glutSolidCube(
        1.0f
    );

    glPopMatrix();

    /* left arm */

    glPushMatrix();

    glTranslatef(
        -0.55f,
        2.25f,
        0.0f
    );

    glRotatef(
        armSwing,
        1.0f,
        0.0f,
        0.0f
    );

    glTranslatef(
        0.0f,
        -0.55f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.18f,
        1.1f,
        0.18f,

        0.03f,
        0.03f,
        0.04f
    );

    glPopMatrix();

    /* right arm */

    glPushMatrix();

    glTranslatef(
        0.55f,
        2.25f,
        0.0f
    );

    glRotatef(
        -armSwing,
        1.0f,
        0.0f,
        0.0f
    );

    glTranslatef(
        0.0f,
        -0.55f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.18f,
        1.1f,
        0.18f,

        0.03f,
        0.03f,
        0.04f
    );

    glPopMatrix();

    /* left leg */

    glPushMatrix();

    glTranslatef(
        -0.18f,
        1.20f,
        0.0f
    );

    glRotatef(
        legSwing,
        1.0f,
        0.0f,
        0.0f
    );

    glTranslatef(
        0.0f,
        -0.60f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.22f,
        1.2f,
        0.25f,

        0.04f,
        0.04f,
        0.05f
    );

    glPopMatrix();

    /* right leg */

    glPushMatrix();

    glTranslatef(
        0.18f,
        1.20f,
        0.0f
    );

    glRotatef(
        -legSwing,
        1.0f,
        0.0f,
        0.0f
    );

    glTranslatef(
        0.0f,
        -0.60f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.22f,
        1.2f,
        0.25f,

        0.04f,
        0.04f,
        0.05f
    );

    glPopMatrix();

    /* head */

    glPushMatrix();

    glTranslatef(
        0.0f,
        2.95f,
        0.0f
    );

    glRotatef(
        personHeadAngle,
        0.0f,
        1.0f,
        0.0f
    );

    setMaterial(
        0.30f,
        0.27f,
        0.23f,
        1.0f,
        10.0f
    );

    glutSolidSphere(
        0.34,
        22,
        22
    );

    /* hair */

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.05f,
        0.20f
    );

    setMaterial(
        0.02f,
        0.02f,
        0.02f,
        1.0f,
        5.0f
    );

    glutSolidSphere(
        0.26,
        18,
        18
    );

    glPopMatrix();

    /* creepy eyes if needed */

    if(personCreepyMode)
    {
        setMaterial(
            0.8f,
            0.0f,
            0.0f,
            1.0f,
            5.0f
        );

        glPushMatrix();

        glTranslatef(
            -0.10f,
            0.05f,
            0.45f
        );

        glutSolidSphere(
            0.03,
            10,
            10
        );

        glPopMatrix();

        glPushMatrix();

        glTranslatef(
            0.10f,
            0.05f,
            0.45f
        );

        glutSolidSphere(
            0.03,
            10,
            10
        );

        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   PAINTING
   ============================================================ */

void drawPainting(void)
{
    float shakeAngle =
        0.0f;

    glPushMatrix();

    if(paintingHaunted)
    {
        shakeAngle =
            5.0f *
            sinf(
                gameTime *
                13.0f
            );
    }

    glTranslatef(
        1.0f,
        3.5f,
        -6.75f
    );

    glRotatef(
        shakeAngle,
        0.0f,
        0.0f,
        1.0f
    );

    /* frame */

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        2.3f,
        2.0f,
        0.15f,

        0.25f,
        0.07f,
        0.02f
    );

    /* picture */

    drawCube(
        0.0f,
        0.0f,
        0.10f,

        1.9f,
        1.6f,
        0.05f,

        0.035f,
        0.035f,
        0.045f
    );

    /* red eyes */

    setMaterial(
        0.75f,
        0.0f,
        0.0f,
        1.0f,
        5.0f
    );

    glPushMatrix();

    glTranslatef(
        -0.35f,
        0.20f,
        0.18f
    );

    glutSolidSphere(
        0.08,
        10,
        10
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.35f,
        0.20f,
        0.18f
    );

    glutSolidSphere(
        0.08,
        10,
        10
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   CUPBOARD
   ============================================================ */

void drawCupboard(void)
{
    glPushMatrix();

    glTranslatef(
        -4.6f,
        0.0f,
        3.7f
    );

    drawCube(
        0.0f,
        2.0f,
        0.0f,

        2.2f,
        4.0f,
        1.5f,

        0.18f,
        0.05f,
        0.02f
    );

    /* moving cupboard door */

    glPushMatrix();

    glTranslatef(
        -1.05f,
        2.0f,
        -0.78f
    );

    glRotatef(
        cupboardDoorAngle,
        0.0f,
        1.0f,
        0.0f
    );

    drawCube(
        0.52f,
        0.0f,
        0.0f,

        1.0f,
        3.6f,
        0.10f,

        0.27f,
        0.08f,
        0.02f
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   CLOCK
   ============================================================ */

void drawClock(void)
{
    float minuteAngle;
    float hourAngle;

    if(clockHaunted)
    {
        minuteAngle =
            gameTime *
            260.0f;

        hourAngle =
            gameTime *
            170.0f;
    }
    else
    {
        minuteAngle =
            clockMinuteAngle;

        hourAngle =
            clockHourAngle;
    }

    glPushMatrix();

    glTranslatef(
        4.4f,
        3.8f,
        -6.75f
    );

    setMaterial(
        0.35f,
        0.15f,
        0.04f,
        1.0f,
        20.0f
    );

    glutSolidTorus(
        0.12,
        0.65,
        20,
        30
    );

    setMaterial(
        0.55f,
        0.52f,
        0.43f,
        1.0f,
        5.0f
    );

    glutSolidSphere(
        0.50,
        20,
        20
    );

    /* minute hand */

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.0f,
        0.48f
    );

    glRotatef(
        minuteAngle,
        0.0f,
        0.0f,
        1.0f
    );

    drawCube(
        0.0f,
        0.28f,
        0.0f,

        0.05f,
        0.55f,
        0.04f,

        0.03f,
        0.03f,
        0.03f
    );

    glPopMatrix();

    /* hour hand */

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.0f,
        0.50f
    );

    glRotatef(
        hourAngle,
        0.0f,
        0.0f,
        1.0f
    );

    drawCube(
        0.0f,
        0.20f,
        0.0f,

        0.07f,
        0.40f,
        0.05f,

        0.02f,
        0.02f,
        0.02f
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   DOOR
   ============================================================ */

void drawDoor(void)
{
    float creepyOffset =
        0.0f;

    glPushMatrix();

    glTranslatef(
        -1.8f,
        2.0f,
        6.85f
    );

    if(
        hauntedDoor &&
        !doorMoving &&
        !doorSlamming
    )
    {
        creepyOffset =
            2.0f *
            sinf(
                gameTime *
                1.7f
            );
    }

    glRotatef(
        doorAngle +
        creepyOffset,

        0.0f,
        1.0f,
        0.0f
    );

    drawCube(
        1.8f,
        0.0f,
        0.0f,

        3.6f,
        4.0f,
        0.25f,

        0.27f,
        0.07f,
        0.02f
    );

    /* handle */

    setMaterial(
        0.75f,
        0.55f,
        0.10f,
        1.0f,
        60.0f
    );

    glPushMatrix();

    glTranslatef(
        3.2f,
        0.0f,
        -0.18f
    );

    glutSolidSphere(
        0.12,
        16,
        16
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   FAN
   ============================================================ */

void drawFan(void)
{
    int i;

    glPushMatrix();

    glTranslatef(
        0.0f,
        5.5f,
        0.0f
    );

    setMaterial(
        0.12f,
        0.12f,
        0.12f,
        1.0f,
        20.0f
    );

    glutSolidSphere(
        0.30,
        18,
        18
    );

    glRotatef(
        fanAngle,
        0.0f,
        1.0f,
        0.0f
    );

    for(
        i = 0;
        i < 4;
        i++
    )
    {
        glPushMatrix();

        glRotatef(
            i * 90.0f,
            0.0f,
            1.0f,
            0.0f
        );

        drawCube(
            1.5f,
            0.0f,
            0.0f,

            2.8f,
            0.08f,
            0.35f,

            0.15f,
            0.05f,
            0.02f
        );

        glPopMatrix();
    }

    glPopMatrix();
}

/* ============================================================
   CANDLE
   ============================================================ */

void drawCandle(void)
{
    glPushMatrix();

    glTranslatef(
        2.4f,
        1.65f,
        -2.5f
    );

    /* candle body */

    glPushMatrix();

    glRotatef(
        -90.0f,
        1.0f,
        0.0f,
        0.0f
    );

    setMaterial(
        0.75f,
        0.68f,
        0.50f,
        1.0f,
        10.0f
    );

    glutSolidCylinder(
        0.13,
        0.55,
        20,
        10
    );

    glPopMatrix();

    /* flame */

    if(
        candleOn &&
        candleFlameScale > 0.001f
    )
    {
        float flameHeight;

        flameHeight =
            1.0f
            +
            0.15f *
            sinf(
                gameTime *
                13.0f
            )
            +
            0.06f *
            sinf(
                gameTime *
                23.0f
            );

        glPushMatrix();

        glTranslatef(
            0.0f,
            0.72f,
            0.0f
        );

        glScalef(
            0.12f *
            candleFlameScale,

            0.25f *
            flameHeight *
            candleFlameScale,

            0.12f *
            candleFlameScale
        );

        setMaterial(
            1.0f,
            0.35f,
            0.02f,
            1.0f,
            5.0f
        );

        glutSolidSphere(
            1.0,
            15,
            15
        );

        glPopMatrix();
    }

    glPopMatrix();
}

/* ============================================================
   SKULL
   ============================================================ */

void drawSkull(void)
{
    float extraY =
        0.0f;

    glPushMatrix();

    if(levitationActive)
    {
        extraY =
            0.8f
            +
            0.25f *
            sinf(
                gameTime *
                2.0f
            );
    }

    glTranslatef(
        3.2f,
        1.95f +
        extraY,
        -2.5f
    );

    if(levitationActive)
    {
        glRotatef(
            gameTime *
            35.0f,

            0.0f,
            1.0f,
            0.0f
        );
    }

    setMaterial(
        0.70f,
        0.66f,
        0.53f,
        1.0f,
        10.0f
    );

    glPushMatrix();

    glScalef(
        0.45f,
        0.55f,
        0.40f
    );

    glutSolidSphere(
        1.0,
        20,
        20
    );

    glPopMatrix();

    /* eye sockets */

    setMaterial(
        0.01f,
        0.01f,
        0.01f,
        1.0f,
        5.0f
    );

    glPushMatrix();

    glTranslatef(
        -0.16f,
        0.1f,
        0.36f
    );

    glutSolidSphere(
        0.08,
        10,
        10
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.16f,
        0.1f,
        0.36f
    );

    glutSolidSphere(
        0.08,
        10,
        10
    );

    glPopMatrix();

    glPopMatrix();
}

/* ============================================================
   FLOATING BOOKS
   ============================================================ */

void drawBooks(void)
{
    float y1 = 0.0f;
    float y2 = 0.0f;
    float y3 = 0.0f;

    float rot1 = 0.0f;
    float rot2 = 0.0f;
    float rot3 = 0.0f;

    if(booksHaunted)
    {
        y1 =
            0.8f +
            0.25f *
            sinf(
                gameTime *
                2.0f
            );

        y2 =
            1.1f +
            0.30f *
            sinf(
                gameTime *
                2.5f
            );

        y3 =
            0.65f +
            0.20f *
            sinf(
                gameTime *
                1.7f
            );

        rot1 =
            gameTime *
            30.0f;

        rot2 =
            -gameTime *
            40.0f;

        rot3 =
            gameTime *
            25.0f;
    }

    /* book 1 */

    glPushMatrix();

    glTranslatef(
        -4.8f,
        1.2f + y1,
        2.4f
    );

    glRotatef(
        rot1,
        0.0f,
        1.0f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.8f,
        0.12f,
        1.1f,

        0.30f,
        0.02f,
        0.02f
    );

    glPopMatrix();

    /* book 2 */

    glPushMatrix();

    glTranslatef(
        -4.1f,
        1.4f + y2,
        2.2f
    );

    glRotatef(
        rot2,
        0.0f,
        1.0f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.7f,
        0.12f,
        1.0f,

        0.04f,
        0.15f,
        0.25f
    );

    glPopMatrix();

    /* book 3 */

    glPushMatrix();

    glTranslatef(
        -3.6f,
        1.0f + y3,
        2.6f
    );

    glRotatef(
        rot3,
        0.0f,
        1.0f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.75f,
        0.12f,
        1.0f,

        0.15f,
        0.05f,
        0.20f
    );

    glPopMatrix();
}

/* ============================================================
   SCARY 3D GHOST
   ============================================================ */

void drawGhost(void)
{
    float floatY;
    float armWave;

    if(
        ghostAlpha <=
        0.01f
    )
    {
        return;
    }

    glEnable(
        GL_BLEND
    );

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glDepthMask(
        GL_FALSE
    );

    glPushMatrix();

    floatY =
        ghostY
        +
        0.22f *
        sinf(
            gameTime *
            2.2f
        );

    armWave =
        18.0f *
        sinf(
            gameTime *
            1.7f
        );

    glTranslatef(
        ghostX,
        floatY,
        ghostZ
    );

    glScalef(
        ghostScale,
        ghostScale,
        ghostScale
    );

    /* main torso */

    setMaterial(
        0.62f,
        0.78f,
        0.82f,
        ghostAlpha,
        10.0f
    );

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.15f,
        0.0f
    );

    glScalef(
        0.65f,
        1.0f,
        0.45f
    );

    glutSolidSphere(
        1.0,
        24,
        24
    );

    glPopMatrix();

    /* head */

    glPushMatrix();

    glTranslatef(
        0.0f,
        1.05f,
        0.0f
    );

    glScalef(
        0.85f,
        0.95f,
        0.80f
    );

    glutSolidSphere(
        0.55,
        24,
        24
    );

    glPopMatrix();

    /* open dark mouth */

    glPushMatrix();

    glTranslatef(
        0.0f,
        0.75f,
        0.32f
    );

    setMaterial(
        0.08f,
        0.01f,
        0.01f,
        ghostAlpha,
        5.0f
    );

    glScalef(
        0.28f,
        0.22f,
        0.12f
    );

    glutSolidSphere(
        1.0,
        16,
        16
    );

    glPopMatrix();

    /* red eyes */

    setMaterial(
        0.95f,
        0.02f,
        0.02f,
        ghostAlpha,
        5.0f
    );

    glPushMatrix();

    glTranslatef(
        -0.18f,
        1.12f,
        0.38f
    );

    glutSolidSphere(
        0.09,
        12,
        12
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.18f,
        1.12f,
        0.38f
    );

    glutSolidSphere(
        0.09,
        12,
        12
    );

    glPopMatrix();

    /* restore ghost material */

    setMaterial(
        0.62f,
        0.78f,
        0.82f,
        ghostAlpha,
        10.0f
    );

    /* left arm */

    glPushMatrix();

    glTranslatef(
        -0.55f,
        0.45f,
        0.0f
    );

    glRotatef(
        -35.0f -
        armWave,

        0.0f,
        0.0f,
        1.0f
    );

    glTranslatef(
        -0.45f,
        0.0f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.75f,
        0.12f,
        0.12f,

        0.62f,
        0.78f,
        0.82f
    );

    /* claws */

    glPushMatrix();

    glTranslatef(
        -0.40f,
        0.0f,
        0.0f
    );

    glRotatef(
        90.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.05,
        0.20,
        8,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        -0.38f,
        0.08f,
        0.06f
    );

    glRotatef(
        95.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.04,
        0.16,
        8,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        -0.38f,
        -0.08f,
        -0.06f
    );

    glRotatef(
        85.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.04,
        0.16,
        8,
        8
    );

    glPopMatrix();

    glPopMatrix();

    /* right arm */

    glPushMatrix();

    glTranslatef(
        0.55f,
        0.45f,
        0.0f
    );

    glRotatef(
        35.0f +
        armWave,

        0.0f,
        0.0f,
        1.0f
    );

    glTranslatef(
        0.45f,
        0.0f,
        0.0f
    );

    drawCube(
        0.0f,
        0.0f,
        0.0f,

        0.75f,
        0.12f,
        0.12f,

        0.62f,
        0.78f,
        0.82f
    );

    /* claws */

    glPushMatrix();

    glTranslatef(
        0.40f,
        0.0f,
        0.0f
    );

    glRotatef(
        -90.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.05,
        0.20,
        8,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.38f,
        0.08f,
        0.06f
    );

    glRotatef(
        -95.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.04,
        0.16,
        8,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.38f,
        -0.08f,
        -0.06f
    );

    glRotatef(
        -85.0f,
        0.0f,
        1.0f,
        0.0f
    );

    glutSolidCone(
        0.04,
        0.16,
        8,
        8
    );

    glPopMatrix();

    glPopMatrix();

    /* lower ghost body */

    glPushMatrix();

    glTranslatef(
        0.0f,
        -0.55f,
        0.0f
    );

    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );

    setMaterial(
        0.62f,
        0.78f,
        0.82f,
        ghostAlpha,
        10.0f
    );

    glutSolidCone(
        0.55,
        1.25,
        24,
        20
    );

    glPopMatrix();

    /* torn tails */

    glPushMatrix();

    glTranslatef(
        -0.25f,
        -1.0f,
        0.05f
    );

    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );

    glutSolidCone(
        0.12,
        0.55,
        12,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.0f,
        -1.12f,
        -0.05f
    );

    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );

    glutSolidCone(
        0.14,
        0.65,
        12,
        8
    );

    glPopMatrix();

    glPushMatrix();

    glTranslatef(
        0.25f,
        -0.98f,
        0.03f
    );

    glRotatef(
        90.0f,
        1.0f,
        0.0f,
        0.0f
    );

    glutSolidCone(
        0.12,
        0.55,
        12,
        8
    );

    glPopMatrix();

    glPopMatrix();

    glDepthMask(
        GL_TRUE
    );

    glDisable(
        GL_BLEND
    );
}

/* ============================================================
   LIGHTING
   ============================================================ */

void setupLighting(void)
{
    glEnable(
        GL_LIGHTING
    );

    /* ========================================================
       CEILING LIGHT
       ======================================================== */

    if(
        mainLightOn &&
        !blackout
    )
    {
        GLfloat position[] =
        {
            0.0f,
            5.5f,
            0.0f,
            1.0f
        };

        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];

        if(ghostDarkMode)
        {
            /* darker room when ghost appears */

            ambient[0] = 0.010f;
            ambient[1] = 0.010f;
            ambient[2] = 0.018f;
            ambient[3] = 1.0f;

            diffuse[0] = 0.08f;
            diffuse[1] = 0.07f;
            diffuse[2] = 0.10f;
            diffuse[3] = 1.0f;

            specular[0] = 0.10f;
            specular[1] = 0.10f;
            specular[2] = 0.13f;
            specular[3] = 1.0f;
        }
        else
        {
            ambient[0] = 0.06f;
            ambient[1] = 0.06f;
            ambient[2] = 0.06f;
            ambient[3] = 1.0f;

            diffuse[0] = 0.50f;
            diffuse[1] = 0.44f;
            diffuse[2] = 0.36f;
            diffuse[3] = 1.0f;

            specular[0] = 0.45f;
            specular[1] = 0.45f;
            specular[2] = 0.45f;
            specular[3] = 1.0f;
        }

        glEnable(
            GL_LIGHT0
        );

        glLightfv(
            GL_LIGHT0,
            GL_POSITION,
            position
        );

        glLightfv(
            GL_LIGHT0,
            GL_AMBIENT,
            ambient
        );

        glLightfv(
            GL_LIGHT0,
            GL_DIFFUSE,
            diffuse
        );

        glLightfv(
            GL_LIGHT0,
            GL_SPECULAR,
            specular
        );
    }
    else
    {
        glDisable(
            GL_LIGHT0
        );
    }

    /* ========================================================
       CANDLE LIGHT
       ======================================================== */

    if(
        candleOn &&
        !blackout &&
        candleFlameScale > 0.001f
    )
    {
        float flicker;

        GLfloat position[] =
        {
            2.4f,
            2.3f,
            -2.5f,
            1.0f
        };

        GLfloat diffuse[4];
        GLfloat ambient[] =
        {
            0.03f,
            0.01f,
            0.005f,
            1.0f
        };

        flicker =
            0.60f
            +
            0.12f *
            sinf(
                gameTime *
                12.0f
            )
            +
            0.05f *
            sinf(
                gameTime *
                21.0f
            );

        flicker *=
            candleFlameScale;

        diffuse[0] =
            flicker;

        diffuse[1] =
            flicker *
            0.42f;

        diffuse[2] =
            0.05f *
            candleFlameScale;

        diffuse[3] =
            1.0f;

        glEnable(
            GL_LIGHT1
        );

        glLightfv(
            GL_LIGHT1,
            GL_POSITION,
            position
        );

        glLightfv(
            GL_LIGHT1,
            GL_DIFFUSE,
            diffuse
        );

        glLightfv(
            GL_LIGHT1,
            GL_AMBIENT,
            ambient
        );
    }
    else
    {
        glDisable(
            GL_LIGHT1
        );
    }

    /* ========================================================
       MOON LIGHT
       ======================================================== */

    if(
        moonLightOn &&
        !blackout
    )
    {
        GLfloat position[] =
        {
            -4.5f,
            4.5f,
            -5.5f,
            1.0f
        };

        GLfloat diffuse[4];
        GLfloat ambient[4];

        if(ghostDarkMode)
        {
            /* colder blue moonlight */

            diffuse[0] = 0.08f;
            diffuse[1] = 0.16f;
            diffuse[2] = 0.50f;
            diffuse[3] = 1.0f;

            ambient[0] = 0.015f;
            ambient[1] = 0.025f;
            ambient[2] = 0.10f;
            ambient[3] = 1.0f;
        }
        else
        {
            diffuse[0] = 0.10f;
            diffuse[1] = 0.18f;
            diffuse[2] = 0.45f;
            diffuse[3] = 1.0f;

            ambient[0] = 0.015f;
            ambient[1] = 0.02f;
            ambient[2] = 0.08f;
            ambient[3] = 1.0f;
        }

        glEnable(
            GL_LIGHT2
        );

        glLightfv(
            GL_LIGHT2,
            GL_POSITION,
            position
        );

        glLightfv(
            GL_LIGHT2,
            GL_DIFFUSE,
            diffuse
        );

        glLightfv(
            GL_LIGHT2,
            GL_AMBIENT,
            ambient
        );
    }
    else
    {
        glDisable(
            GL_LIGHT2
        );
    }

    /* ========================================================
       RED PARANORMAL LIGHT
       ======================================================== */

    if(
        redLight &&
        !blackout
    )
    {
        GLfloat position[] =
        {
            0.0f,
            3.0f,
            -2.0f,
            1.0f
        };

        GLfloat diffuse[] =
        {
            0.65f,
            0.01f,
            0.01f,
            1.0f
        };

        GLfloat ambient[] =
        {
            0.08f,
            0.0f,
            0.0f,
            1.0f
        };

        glEnable(
            GL_LIGHT3
        );

        glLightfv(
            GL_LIGHT3,
            GL_POSITION,
            position
        );

        glLightfv(
            GL_LIGHT3,
            GL_DIFFUSE,
            diffuse
        );

        glLightfv(
            GL_LIGHT3,
            GL_AMBIENT,
            ambient
        );
    }
    else
    {
        glDisable(
            GL_LIGHT3
        );
    }

    /* ========================================================
       LIGHTNING
       ======================================================== */

    if(lightningActive)
    {
        GLfloat position[] =
        {
            -3.0f,
            5.0f,
            -5.0f,
            1.0f
        };

        GLfloat diffuse[] =
        {
            1.0f,
            1.0f,
            1.0f,
            1.0f
        };

        GLfloat ambient[] =
        {
            0.40f,
            0.45f,
            0.60f,
            1.0f
        };

        glEnable(
            GL_LIGHT4
        );

        glLightfv(
            GL_LIGHT4,
            GL_POSITION,
            position
        );

        glLightfv(
            GL_LIGHT4,
            GL_DIFFUSE,
            diffuse
        );

        glLightfv(
            GL_LIGHT4,
            GL_AMBIENT,
            ambient
        );
    }
    else
    {
        glDisable(
            GL_LIGHT4
        );
    }
}

/* ============================================================
   CAMERA
   ============================================================ */

void setupCamera(void)
{
    float dirX;
    float dirZ;
    float lookY;

    dirX =
        sinf(
            cameraYaw
        );

    dirZ =
        -cosf(
            cameraYaw
        );

    lookY =
        cameraY
        +
        sinf(
            cameraPitch
        );

    gluLookAt(
        cameraX,
        cameraY,
        cameraZ,

        cameraX + dirX,
        lookY,
        cameraZ + dirZ,

        0.0f,
        1.0f,
        0.0f
    );
}

/* ============================================================
   COLLISION
   ============================================================ */

int validPosition(
    float x,
    float z
)
{
    /* walls */

    if(
        x < -5.6f ||
        x > 5.6f ||
        z < -6.5f ||
        z > 6.5f
    )
    {
        return 0;
    }

    /* bed */

    if(
        x > -5.6f &&
        x < -1.6f &&
        z > -5.1f &&
        z < 0.3f
    )
    {
        return 0;
    }

    /* table */

    if(
        x > 0.8f &&
        x < 4.4f &&
        z > -3.8f &&
        z < -1.1f
    )
    {
        return 0;
    }

    /* cupboard */

    if(
        x > -5.8f &&
        x < -3.3f &&
        z > 2.7f &&
        z < 4.8f
    )
    {
        return 0;
    }

    return 1;
}

/* ============================================================
   EVENTS
   ============================================================ */

void triggerDoor(void)
{
    doorMoving = 1;
    hauntedDoor = 1;

    if(
        doorAngle <
        40.0f
    )
    {
        doorOpening =
            1;
    }
    else
    {
        doorOpening =
            0;
    }
}

/* ============================================================ */

void triggerFlicker(void)
{
    flickering =
        1;

    flickerStartTime =
        gameTime;
}

/* ============================================================ */

void triggerLightning(void)
{
    lightningActive =
        1;

    lightningStartTime =
        gameTime;
}

/* ============================================================
   GHOST APPEARS FROM WINDOW
   ============================================================ */

void startGhostWindowEvent(void)
{
    ghostActive =
        1;

    ghostEmerging =
        1;

    ghostFollowMode =
        0;

    ghostAlpha =
        0.0f;

    ghostScale =
        0.12f;

    /* starts outside / inside window */

    ghostX =
        -3.15f;

    ghostY =
        3.15f;

    ghostZ =
        -6.55f;

    /* target inside room */

    ghostTargetX =
        -2.15f;

    ghostTargetY =
        2.65f;

    ghostTargetZ =
        -5.15f;

    /* ========================================================
       NEW ATMOSPHERE
       ======================================================== */

    /* room becomes darker */

    ghostDarkMode =
        1;

    /* candle begins dying */

    candleFlameScale =
        1.0f;

    candleOn =
        1;

    /* moonlight stays */

    moonLightOn =
        1;

    /* scare person */

    if(
        personVisible &&
        !personEscaped
    )
    {
        personScared =
            1;

        personRunning =
            0;

        personReactionStartTime =
            gameTime;

        personCreepyMode =
            0;
    }
}

/* ============================================================
   RESET
   ============================================================ */

void resetHaunting(void)
{
    doorAngle =
        0.0f;

    doorMoving =
        0;

    doorOpening =
        1;

    hauntedDoor =
        0;

    doorSlamming =
        0;

    mainLightOn =
        1;

    candleOn =
        1;

    candleFlameScale =
        1.0f;

    moonLightOn =
        1;

    ghostDarkMode =
        0;

    flickering =
        0;

    blackout =
        0;

    redLight =
        0;

    lightningActive =
        0;

    fanMode =
        1;

    fanSpeed =
        2.0f;

    ghostActive =
        0;

    ghostFollowMode =
        0;

    ghostEmerging =
        0;

    ghostAlpha =
        0.0f;

    ghostScale =
        0.1f;

    ghostX =
        -3.1f;

    ghostY =
        3.2f;

    ghostZ =
        -6.5f;

    personVisible =
        1;

    personTurning =
        0;

    personCreepyMode =
        0;

    personScared =
        0;

    personRunning =
        0;

    personEscaped =
        0;

    personHeadAngle =
        0.0f;

    personBodyAngle =
        180.0f;

    personX =
        -1.6f;

    personZ =
        -5.8f;

    chairMoving =
        0;

    chairOffsetX =
        0.0f;

    chairOffsetZ =
        0.0f;

    paintingHaunted =
        0;

    levitationActive =
        0;

    cupboardOpening =
        0;

    cupboardDoorAngle =
        0.0f;

    bedShaking =
        0;

    curtainsMoving =
        1;

    clockHaunted =
        0;

    booksHaunted =
        0;

    paranormalSequence =
        0;

    sequenceStage =
        0;

    horrorIncident =
        0;

    horrorStage =
        0;
}

/* ============================================================
   FULL PARANORMAL SEQUENCE
   ============================================================ */

void updateParanormalSequence(void)
{
    float t;

    if(!paranormalSequence)
    {
        return;
    }

    t =
        gameTime -
        sequenceStartTime;

    /* painting */

    if(
        t >= 1.0f &&
        sequenceStage == 0
    )
    {
        paintingHaunted =
            1;

        sequenceStage =
            1;
    }

    /* lights */

    if(
        t >= 3.0f &&
        sequenceStage == 1
    )
    {
        triggerFlicker();

        sequenceStage =
            2;
    }

    /* chair + clock */

    if(
        t >= 5.0f &&
        sequenceStage == 2
    )
    {
        chairMoving =
            1;

        clockHaunted =
            1;

        sequenceStage =
            3;
    }

    /* levitation */

    if(
        t >= 7.0f &&
        sequenceStage == 3
    )
    {
        levitationActive =
            1;

        booksHaunted =
            1;

        bedShaking =
            1;

        sequenceStage =
            4;
    }

    /* ghost at window */

    if(
        t >= 9.0f &&
        sequenceStage == 4
    )
    {
        triggerLightning();

        startGhostWindowEvent();

        sequenceStage =
            5;
    }

    /* red light + cupboard */

    if(
        t >= 13.0f &&
        sequenceStage == 5
    )
    {
        redLight =
            1;

        cupboardOpening =
            1;

        sequenceStage =
            6;
    }

    /* crazy fan + ghost follows */

    if(
        t >= 15.0f &&
        sequenceStage == 6
    )
    {
        fanMode =
            2;

        fanSpeed =
            16.0f;

        ghostFollowMode =
            1;

        sequenceStage =
            7;
    }

    /* door slam */

    if(
        t >= 17.0f &&
        sequenceStage == 7
    )
    {
        doorAngle =
            80.0f;

        doorSlamming =
            1;

        sequenceStage =
            8;
    }

    if(t >= 20.0f)
    {
        paranormalSequence =
            0;
    }
}

/* ============================================================
   SUDDEN HORROR INCIDENT
   ============================================================ */

void updateHorrorIncident(void)
{
    float t;

    if(!horrorIncident)
    {
        return;
    }

    t =
        gameTime -
        horrorStartTime;

    /* blackout */

    if(
        t >= 0.0f &&
        horrorStage == 0
    )
    {
        blackout =
            1;

        horrorStage =
            1;
    }

    /* lightning */

    if(
        t >= 1.0f &&
        horrorStage == 1
    )
    {
        blackout =
            0;

        triggerLightning();

        horrorStage =
            2;
    }

    /* ghost appears */

    if(
        t >= 1.4f &&
        horrorStage == 2
    )
    {
        startGhostWindowEvent();

        horrorStage =
            3;
    }

    /* room becomes crazy */

    if(
        t >= 3.5f &&
        horrorStage == 3
    )
    {
        redLight =
            1;

        booksHaunted =
            1;

        paintingHaunted =
            1;

        horrorStage =
            4;
    }

    /* door slam */

    if(
        t >= 4.8f &&
        horrorStage == 4
    )
    {
        doorAngle =
            80.0f;

        doorSlamming =
            1;

        horrorStage =
            5;
    }

    if(t >= 6.0f)
    {
        horrorIncident =
            0;
    }
}

/* ============================================================
   UPDATE
   ============================================================ */

void update(int value)
{
    gameTime +=
        0.016f;

    /* ========================================================
       CLOCK
       ======================================================== */

    clockMinuteAngle +=
        0.15f;

    clockHourAngle +=
        0.015f;

    if(
        clockMinuteAngle >=
        360.0f
    )
    {
        clockMinuteAngle -=
            360.0f;
    }

    if(
        clockHourAngle >=
        360.0f
    )
    {
        clockHourAngle -=
            360.0f;
    }

    /* ========================================================
       FAN
       ======================================================== */

    if(fanMode != 0)
    {
        fanAngle +=
            fanSpeed;

        if(
            fanAngle >
            360.0f
        )
        {
            fanAngle -=
                360.0f;
        }
    }

    /* ========================================================
       DOOR MOVEMENT
       ======================================================== */

    if(doorMoving)
    {
        if(doorOpening)
        {
            doorAngle +=
                0.7f;

            if(
                doorAngle >=
                80.0f
            )
            {
                doorAngle =
                    80.0f;

                doorMoving =
                    0;
            }
        }
        else
        {
            doorAngle -=
                0.9f;

            if(
                doorAngle <=
                0.0f
            )
            {
                doorAngle =
                    0.0f;

                doorMoving =
                    0;
            }
        }
    }

    /* ========================================================
       DOOR SLAM
       ======================================================== */

    if(doorSlamming)
    {
        doorAngle -=
            6.0f;

        if(
            doorAngle <=
            0.0f
        )
        {
            doorAngle =
                0.0f;

            doorSlamming =
                0;

            hauntedDoor =
                0;
        }
    }

    /* ========================================================
       LIGHT FLICKER
       ======================================================== */

    if(flickering)
    {
        float elapsed;

        float flickerValue;

        elapsed =
            gameTime -
            flickerStartTime;

        flickerValue =
            sinf(
                gameTime *
                17.0f
            )
            +
            sinf(
                gameTime *
                31.0f
            );

        if(
            flickerValue >
            0.0f
        )
        {
            mainLightOn =
                1;
        }
        else
        {
            mainLightOn =
                0;
        }

        if(
            elapsed >
            4.0f
        )
        {
            flickering =
                0;

            mainLightOn =
                1;
        }
    }

    /* ========================================================
       LIGHTNING DURATION
       ======================================================== */

    if(lightningActive)
    {
        if(
            gameTime -
            lightningStartTime >
            0.20f
        )
        {
            lightningActive =
                0;
        }
    }

    /* ========================================================
       CANDLE DIES WHEN GHOST APPEARS
       ======================================================== */

    if(
        ghostDarkMode &&
        candleOn
    )
    {
        candleFlameScale -=
            0.035f;

        if(
            candleFlameScale <=
            0.0f
        )
        {
            candleFlameScale =
                0.0f;

            candleOn =
                0;
        }
    }

    /* ========================================================
       GHOST FADE AND SCALE
       ======================================================== */

    if(ghostActive)
    {
        ghostAlpha +=
            0.008f;

        if(
            ghostAlpha >
            0.70f
        )
        {
            ghostAlpha =
                0.70f;
        }

        ghostScale +=
            0.012f;

        if(
            ghostScale >
            1.0f
        )
        {
            ghostScale =
                1.0f;
        }
    }
    else
    {
        ghostAlpha -=
            0.015f;

        if(
            ghostAlpha <
            0.0f
        )
        {
            ghostAlpha =
                0.0f;
        }
    }

    /* ========================================================
       GHOST EMERGES FROM WINDOW
       ======================================================== */

    if(ghostEmerging)
    {
        float dx;
        float dy;
        float dz;
        float len;

        dx =
            ghostTargetX -
            ghostX;

        dy =
            ghostTargetY -
            ghostY;

        dz =
            ghostTargetZ -
            ghostZ;

        len =
            sqrtf(
                dx * dx
                +
                dy * dy
                +
                dz * dz
            );

        if(
            len >
            0.05f
        )
        {
            ghostX +=
                (dx / len) *
                0.035f;

            ghostY +=
                (dy / len) *
                0.035f;

            ghostZ +=
                (dz / len) *
                0.035f;
        }
        else
        {
            ghostEmerging =
                0;
        }
    }

    /* ========================================================
       GHOST FOLLOWS CAMERA
       ======================================================== */

    if(
        ghostActive &&
        ghostFollowMode &&
        !ghostEmerging
    )
    {
        float dx;
        float dz;
        float len;

        dx =
            cameraX -
            ghostX;

        dz =
            cameraZ -
            ghostZ;

        len =
            sqrtf(
                dx * dx +
                dz * dz
            );

        if(
            len >
            1.5f
        )
        {
            ghostX +=
                (dx / len) *
                0.008f;

            ghostZ +=
                (dz / len) *
                0.008f;
        }
    }

    /* ========================================================
       PERSON SEES GHOST
       ======================================================== */

    if(
        personScared &&
        personVisible &&
        !personRunning
    )
    {
        if(
            personHeadAngle <
            35.0f
        )
        {
            personHeadAngle +=
                2.0f;
        }

        /* delay before running */

        if(
            gameTime -
            personReactionStartTime >
            0.70f
        )
        {
            personScared =
                0;

            personRunning =
                1;
        }
    }

    /* ========================================================
       PERSON RUNS TOWARD EXIT
       ======================================================== */

    if(
        personRunning &&
        personVisible
    )
    {
        float targetX =
            0.35f;

        float targetZ =
            5.9f;

        float dx;
        float dz;
        float len;

        dx =
            targetX -
            personX;

        dz =
            targetZ -
            personZ;

        len =
            sqrtf(
                dx * dx +
                dz * dz
            );

        if(
            len >
            0.10f
        )
        {
            personX +=
                (dx / len) *
                0.060f;

            personZ +=
                (dz / len) *
                0.060f;

            personBodyAngle =
                atan2f(
                    dx,
                    dz
                )
                *
                180.0f
                /
                PI;

            personHeadAngle =
                10.0f;
        }
        else
        {
            personRunning =
                0;

            personVisible =
                0;

            personEscaped =
                1;
        }
    }

    /* ========================================================
       PERSON HEAD TURN
       ======================================================== */

    if(personTurning)
    {
        personHeadAngle +=
            0.7f;

        if(
            personHeadAngle >=
            180.0f
        )
        {
            personHeadAngle =
                180.0f;

            personTurning =
                0;
        }
    }

    /* ========================================================
       CHAIR
       ======================================================== */

    if(chairMoving)
    {
        chairOffsetX =
            0.7f *
            sinf(
                gameTime *
                1.3f
            );

        chairOffsetZ =
            0.25f *
            sinf(
                gameTime *
                2.1f
            );
    }
    else
    {
        chairOffsetX =
            0.0f;

        chairOffsetZ =
            0.0f;
    }

    /* ========================================================
       CUPBOARD
       ======================================================== */

    if(
        cupboardOpening &&
        cupboardDoorAngle <
        85.0f
    )
    {
        cupboardDoorAngle +=
            0.6f;
    }

    /* scripted events */

    updateParanormalSequence();

    updateHorrorIncident();

    glutPostRedisplay();

    glutTimerFunc(
        16,
        update,
        0
    );
}

/* ============================================================
   TEXT
   ============================================================ */

void drawText(
    float x,
    float y,
    const char *text
)
{
    int i;

    glRasterPos2f(
        x,
        y
    );

    for(
        i = 0;
        text[i] != '\0';
        i++
    )
    {
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_12,
            text[i]
        );
    }
}

/* ============================================================
   HUD
   ============================================================ */

void drawHUD(void)
{
    glDisable(
        GL_LIGHTING
    );

    glDisable(
        GL_DEPTH_TEST
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glPushMatrix();

    glLoadIdentity();

    gluOrtho2D(
        0,
        1200,
        0,
        700
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glPushMatrix();

    glLoadIdentity();

    glColor3f(
        0.90f,
        0.90f,
        0.90f
    );

    drawText(
        20,
        675,
        "THE HAUNTED ROOM - NIGHT"
    );

    drawText(
        20,
        655,
        "WASD Move | Arrow Keys Look"
    );

    drawText(
        20,
        635,
        "1 Door | 2 Flicker | 3 Ghost from Window | 4 Chair | 5 Painting | 6 Levitation"
    );

    drawText(
        20,
        615,
        "7 Moon | 8 Door Slam | 9 Full Haunting | 0 Reset"
    );

    drawText(
        20,
        595,
        "P Reset Person | L Lightning | X Sudden Horror | K Clock | V Books"
    );

    drawText(
        20,
        575,
        "F Fan | C Candle | R Red Light | U Cupboard | B Blackout | H Fog"
    );

    if(paranormalSequence)
    {
        glColor3f(
            1.0f,
            0.2f,
            0.2f
        );

        drawText(
            470,
            650,
            "PARANORMAL ACTIVITY DETECTED"
        );
    }

    if(horrorIncident)
    {
        glColor3f(
            1.0f,
            0.05f,
            0.05f
        );

        drawText(
            520,
            625,
            "WARNING"
        );
    }

    if(
        personRunning
    )
    {
        glColor3f(
            1.0f,
            0.4f,
            0.2f
        );

        drawText(
            500,
            600,
            "THE PERSON IS ESCAPING!"
        );
    }

    glPopMatrix();

    glMatrixMode(
        GL_PROJECTION
    );

    glPopMatrix();

    glMatrixMode(
        GL_MODELVIEW
    );

    glEnable(
        GL_DEPTH_TEST
    );

    glEnable(
        GL_LIGHTING
    );
}

/* ============================================================
   DISPLAY
   ============================================================ */

void display(void)
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();

    setupCamera();

    setupLighting();

    drawRoom();

    drawWindow();

    drawBed();

    drawTable();

    drawChair();

    drawCupboard();

    drawBooks();

    drawPainting();

    drawClock();

    drawDoor();

    drawFan();

    drawCandle();

    drawSkull();

    drawPerson();

    /* ghost last because transparency */

    drawGhost();

    drawHUD();

    glutSwapBuffers();
}

/* ============================================================
   KEYBOARD
   ============================================================ */

void keyboard(
    unsigned char key,
    int x,
    int y
)
{
    float newX =
        cameraX;

    float newZ =
        cameraZ;

    switch(key)
    {
        /* ====================================================
           MOVEMENT
           ==================================================== */

        case 'w':
        case 'W':

            newX +=
                sinf(
                    cameraYaw
                )
                *
                moveSpeed;

            newZ -=
                cosf(
                    cameraYaw
                )
                *
                moveSpeed;

            break;

        case 's':
        case 'S':

            newX -=
                sinf(
                    cameraYaw
                )
                *
                moveSpeed;

            newZ +=
                cosf(
                    cameraYaw
                )
                *
                moveSpeed;

            break;

        case 'a':
        case 'A':

            newX -=
                cosf(
                    cameraYaw
                )
                *
                moveSpeed;

            newZ -=
                sinf(
                    cameraYaw
                )
                *
                moveSpeed;

            break;

        case 'd':
        case 'D':

            newX +=
                cosf(
                    cameraYaw
                )
                *
                moveSpeed;

            newZ +=
                sinf(
                    cameraYaw
                )
                *
                moveSpeed;

            break;

        /* ====================================================
           1 - DOOR
           ==================================================== */

        case '1':

            triggerDoor();

            break;

        /* ====================================================
           2 - LIGHT FLICKER
           ==================================================== */

        case '2':

            triggerFlicker();

            break;

        /* ====================================================
           3 - GHOST FROM WINDOW
           ==================================================== */

        case '3':

            if(!ghostActive)
            {
                startGhostWindowEvent();
            }
            else
            {
                ghostActive =
                    0;

                ghostEmerging =
                    0;

                ghostFollowMode =
                    0;
            }

            break;

        /* ====================================================
           4 - CHAIR
           ==================================================== */

        case '4':

            chairMoving =
                !chairMoving;

            break;

        /* ====================================================
           5 - PAINTING
           ==================================================== */

        case '5':

            paintingHaunted =
                !paintingHaunted;

            break;

        /* ====================================================
           6 - LEVITATION
           ==================================================== */

        case '6':

            levitationActive =
                !levitationActive;

            bedShaking =
                levitationActive;

            break;

        /* ====================================================
           7 - MOON
           ==================================================== */

        case '7':

            moonLightOn =
                !moonLightOn;

            break;

        /* ====================================================
           8 - DOOR SLAM
           ==================================================== */

        case '8':

            if(
                doorAngle <
                20.0f
            )
            {
                doorAngle =
                    80.0f;
            }

            doorSlamming =
                1;

            break;

        /* ====================================================
           9 - FULL HAUNTING
           ==================================================== */

        case '9':

            resetHaunting();

            paranormalSequence =
                1;

            sequenceStartTime =
                gameTime;

            sequenceStage =
                0;

            break;

        /* ====================================================
           0 - RESET
           ==================================================== */

        case '0':

            resetHaunting();

            break;

        /* ====================================================
           P - RESET PERSON
           ==================================================== */

        case 'p':
        case 'P':

            personVisible =
                1;

            personRunning =
                0;

            personScared =
                0;

            personEscaped =
                0;

            personHeadAngle =
                0.0f;

            personBodyAngle =
                180.0f;

            personX =
                -1.6f;

            personZ =
                -5.8f;

            break;

        /* ====================================================
           L - LIGHTNING
           ==================================================== */

        case 'l':
        case 'L':

            triggerLightning();

            break;

        /* ====================================================
           X - SUDDEN HORROR
           ==================================================== */

        case 'x':
        case 'X':

            horrorIncident =
                1;

            horrorStartTime =
                gameTime;

            horrorStage =
                0;

            break;

        /* ====================================================
           K - CLOCK
           ==================================================== */

        case 'k':
        case 'K':

            clockHaunted =
                !clockHaunted;

            break;

        /* ====================================================
           V - BOOKS
           ==================================================== */

        case 'v':
        case 'V':

            booksHaunted =
                !booksHaunted;

            break;

        /* ====================================================
           F - FAN
           ==================================================== */

        case 'f':
        case 'F':

            fanMode++;

            if(
                fanMode >
                2
            )
            {
                fanMode =
                    0;
            }

            if(
                fanMode ==
                0
            )
            {
                fanSpeed =
                    0.0f;
            }

            if(
                fanMode ==
                1
            )
            {
                fanSpeed =
                    2.0f;
            }

            if(
                fanMode ==
                2
            )
            {
                fanSpeed =
                    15.0f;
            }

            break;

        /* ====================================================
           C - CANDLE
           ==================================================== */

        case 'c':
        case 'C':

            candleOn =
                !candleOn;

            if(candleOn)
            {
                candleFlameScale =
                    1.0f;
            }

            break;

        /* ====================================================
           R - RED LIGHT
           ==================================================== */

        case 'r':
        case 'R':

            redLight =
                !redLight;

            break;

        /* ====================================================
           U - CUPBOARD
           ==================================================== */

        case 'u':
        case 'U':

            cupboardOpening =
                !cupboardOpening;

            if(!cupboardOpening)
            {
                cupboardDoorAngle =
                    0.0f;
            }

            break;

        /* ====================================================
           B - BLACKOUT
           ==================================================== */

        case 'b':
        case 'B':

            blackout =
                !blackout;

            break;

        /* ====================================================
           H - FOG
           ==================================================== */

        case 'h':
        case 'H':

            fogEnabled =
                !fogEnabled;

            if(fogEnabled)
            {
                glEnable(
                    GL_FOG
                );
            }
            else
            {
                glDisable(
                    GL_FOG
                );
            }

            break;

        /* ESC */

        case 27:

            exit(0);
    }

    if(
        validPosition(
            newX,
            newZ
        )
    )
    {
        cameraX =
            newX;

        cameraZ =
            newZ;
    }

    glutPostRedisplay();
}

/* ============================================================
   ARROW KEYS
   ============================================================ */

void specialKeys(
    int key,
    int x,
    int y
)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:

            cameraYaw -=
                0.07f;

            break;

        case GLUT_KEY_RIGHT:

            cameraYaw +=
                0.07f;

            break;

        case GLUT_KEY_UP:

            cameraPitch +=
                0.04f;

            if(
                cameraPitch >
                0.7f
            )
            {
                cameraPitch =
                    0.7f;
            }

            break;

        case GLUT_KEY_DOWN:

            cameraPitch -=
                0.04f;

            if(
                cameraPitch <
                -0.7f
            )
            {
                cameraPitch =
                    -0.7f;
            }

            break;
    }

    glutPostRedisplay();
}

/* ============================================================
   RESHAPE
   ============================================================ */

void reshape(
    int width,
    int height
)
{
    float aspect;

    if(height == 0)
    {
        height = 1;
    }

    aspect =
        (float)width /
        (float)height;

    glViewport(
        0,
        0,
        width,
        height
    );

    glMatrixMode(
        GL_PROJECTION
    );

    glLoadIdentity();

    gluPerspective(
        60.0,
        aspect,
        0.1,
        100.0
    );

    glMatrixMode(
        GL_MODELVIEW
    );
}

/* ============================================================
   INITIALIZATION
   ============================================================ */

void init(void)
{
    GLfloat globalAmbient[] =
    {
        0.018f,
        0.018f,
        0.028f,
        1.0f
    };

    GLfloat fogColor[] =
    {
        0.015f,
        0.015f,
        0.025f,
        1.0f
    };

    glEnable(
        GL_DEPTH_TEST
    );

    glEnable(
        GL_NORMALIZE
    );

    glShadeModel(
        GL_SMOOTH
    );

    /* night background */

    glClearColor(
        0.004f,
        0.006f,
        0.018f,
        1.0f
    );

    /* global ambient */

    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        globalAmbient
    );

    /* fog */

    glEnable(
        GL_FOG
    );

    glFogfv(
        GL_FOG_COLOR,
        fogColor
    );

    glFogi(
        GL_FOG_MODE,
        GL_LINEAR
    );

    glFogf(
        GL_FOG_START,
        5.0f
    );

    glFogf(
        GL_FOG_END,
        15.0f
    );
}

/* ============================================================
   MAIN
   ============================================================ */

int main(
    int argc,
    char **argv
)
{
    glutInit(
        &argc,
        argv
    );

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(
        1200,
        700
    );

    glutInitWindowPosition(
        100,
        50
    );

    glutCreateWindow(
        "The Haunted Room - 3D Paranormal Experience"
    );

    init();

    glutDisplayFunc(
        display
    );

    glutReshapeFunc(
        reshape
    );

    glutKeyboardFunc(
        keyboard
    );

    glutSpecialFunc(
        specialKeys
    );

    glutTimerFunc(
        16,
        update,
        0
    );

    printf("\n");
    printf("====================================================\n");
    printf("       THE HAUNTED ROOM - 3D NIGHT EXPERIENCE\n");
    printf("====================================================\n");

    printf("\nMOVEMENT\n");
    printf("WASD   : Move\n");
    printf("Arrows : Look around\n");

    printf("\nPARANORMAL EVENTS\n");
    printf("1 : Haunted door\n");
    printf("2 : Flickering lights\n");
    printf("3 : Ghost appears from window\n");
    printf("    Candle dies, room darkens, person escapes\n");
    printf("4 : Moving chair\n");
    printf("5 : Haunted painting\n");
    printf("6 : Skull levitation + bed shake\n");
    printf("7 : Moonlight\n");
    printf("8 : Door slam\n");
    printf("9 : FULL HAUNTING SEQUENCE\n");
    printf("0 : Reset everything\n");

    printf("\nSPECIAL EFFECTS\n");
    printf("P : Reset person near window\n");
    printf("L : Lightning\n");
    printf("X : Sudden horror incident\n");
    printf("K : Haunted clock\n");
    printf("V : Floating books\n");

    printf("\nENVIRONMENT\n");
    printf("F : Fan speed\n");
    printf("C : Candle\n");
    printf("R : Red paranormal light\n");
    printf("U : Cupboard\n");
    printf("B : Blackout\n");
    printf("H : Fog\n");

    printf("\nESC : Exit\n");

    printf("====================================================\n");

    glutMainLoop();

    return 0;
}
