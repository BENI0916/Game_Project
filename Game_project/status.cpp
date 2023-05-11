#include "lib/var.h"
#include "lib/status.h"

extern PIMAGE bloodLine, blood[], dropImg[];
extern int bp[bpL];

void playerBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],20,680);
    putimage_withalpha(NULL,bloodLine,20,680);
    /*settextjustify(CENTER_TEXT,CENTER_TEXT);
    rectprintf(20,680,300,18,"%d/%d",hp,fhp);*/
}

void monBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],960,680);
    putimage_withalpha(NULL,bloodLine,960,680);
    /*settextjustify(CENTER_TEXT,CENTER_TEXT);
    rectprintf(960,680,300,18,"%d/%d",hp,fhp);*/
}

void putMoney() {
    putimage_withalpha(NULL,dropImg[0],30,640);
    //settextjustify(LEFT_TEXT,TOP_TEXT);
    xyprintf(70,656," x %d",bp[0]);
}