#include <stdio.h>
#include "SkPaint.h"
#include "SkData.h"
#include "SkCanvas.h"
#include "SkPDFDevice.h"
#include "SkPDFDocument.h"
#include "SkTypeface.h"
#include "SkDocument.h"
#include "SkImageEncoder.h"
#include "SkForceLinking.h"
__SK_FORCE_IMAGE_DECODER_LINKING;


int main(int argc, char** argv) {
    SkBitmap bitmap;
    SkImageInfo info = SkImageInfo::MakeN32(200, 200, kPremul_SkAlphaType);
    bitmap.allocPixels(info);

    SkCanvas c(bitmap);
    SkPaint paint;
    SkRect r;

    paint.setColor(SK_ColorWHITE);
    r.set(0, 0, 200, 200);
    c.drawRect(r, paint);

    paint.setColor(SK_ColorBLACK);
    paint.setTextSize(SkIntToScalar(12));
    paint.setHinting(SkPaint::kFull_Hinting);
    paint.setTypeface(SkTypeface::CreateFromName("Comic Sans MS", SkTypeface::kNormal));

    paint.setFakeBoldText(false);
    //paint.setFakeBoldText(true);
    const char text[] = "Hello World!";

    c.drawText(&text, 12, SkIntToScalar(0), SkIntToScalar(50), paint);
    c.drawLine(SkIntToScalar(0), SkIntToScalar(50), SkIntToScalar(100), SkIntToScalar(50), paint);

    {
      SkAutoLockPixels image_lock(bitmap);
      if(!SkImageEncoder::EncodeFile("snapshot-skia.png", bitmap, SkImageEncoder::kPNG_Type, 100))
	fprintf(stderr, "Error when encoding file\n");
    }

    return 0;
}
