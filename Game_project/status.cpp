#include "lib/var.h"
#include "lib/status.h"

extern PIMAGE bloodLine, blood[];

void playerBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],20,680);
    putimage_withalpha(NULL,bloodLine,20,680);
}

void monBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],960,680);
    putimage_withalpha(NULL,bloodLine,960,680);
}
