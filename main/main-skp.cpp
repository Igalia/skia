#include "SkCanvas.h"
#include "SkBitmap.h"
#include "SkBitmapDevice.h"
#include "SkPaint.h"
#include "SkRect.h"
#include "SkImageEncoder.h"
#include "SkPicture.h"
#include "SkPictureRecorder.h"
#include "SkShader.h"
#include "SkColorFilter.h"

#include "SkString.h"
#include "SkStream.h"

#include "SkForceLinking.h"
__SK_FORCE_IMAGE_DECODER_LINKING;

int main()
{
  SkBitmap bitmap;
  SkImageInfo info = SkImageInfo::MakeN32(200, 200, kPremul_SkAlphaType);
  bitmap.allocPixels(info);

  SkCanvas canvas(bitmap);
  SkPaint paint;
  SkRect r;

  canvas.drawColor(SK_ColorWHITE);
  // Draw three rectangles of different colors
  paint.setARGB(127, 0, 0, 255);
  r.set(0, 0, 40, 40);
  canvas.drawRect(r, paint);
 
  {
    SkAutoLockPixels image_lock(bitmap);
    if(!SkImageEncoder::EncodeFile("snapshot-skia.png", bitmap, SkImageEncoder::kPNG_Type, 100))
   		  fprintf(stderr, "Error when encoding file\n");
  }

  SkPictureRecorder pictRec;
  SkCanvas *cv = pictRec.beginRecording(200, 200);

  cv->drawColor(SK_ColorWHITE);
  cv->drawRect(r, paint);
  SkPicture *pict = pictRec.endRecording();

  SkString path("snapshot-skp.skp");
  SkFILEWStream stream(path.c_str());
  pict->serialize(&stream);


  return 0;
}
