#include "SkCanvas.h"
#include "SkBitmap.h"
#include "SkBitmapDevice.h"
#include "SkPaint.h"
#include "SkRect.h"
#include "SkImageEncoder.h"
#include <cairo/cairo.h>

#include "SkShader.h"
#include "SkColorFilter.h"
#include "SkImageInfo.h"

#include <stdio.h>

#include "SkForceLinking.h"
__SK_FORCE_IMAGE_DECODER_LINKING;

SkShader* createChecker() {
	SkBitmap bm;
	SkImageInfo info = SkImageInfo::MakeN32(2, 2, kPremul_SkAlphaType);

	bm.allocPixels(info);
	bm.lockPixels();

	*bm.getAddr32(0,0) = *bm.getAddr32(1,1) = SkPreMultiplyColor(0xFF000000);
	*bm.getAddr32(0,1) = *bm.getAddr32(1,0) = SkPreMultiplyColor(0xFFFFFFFF);

	SkShader* s = SkShader::CreateBitmapShader(bm, SkShader::kRepeat_TileMode,
						   SkShader::kRepeat_TileMode);
	SkMatrix m;
	m.setScale(12,12);
	return s->CreateLocalMatrixShader(s, m);
}

  // Create ColorFilter

SkColorFilter* createColorFilter() {
	static const SkColor gColor = 0x80CCFFCC;
	static const SkXfermode::Mode gMode = SkXfermode::kSrcATop_Mode;
	
	return SkColorFilter::CreateModeFilter(gColor, gMode);
}


int main()
{
  SkBitmap bitmap;
  SkImageInfo info = SkImageInfo::MakeN32(200, 200, kPremul_SkAlphaType);
  bitmap.allocPixels(info);

  SkBitmap bitmapTemp;
  SkImageInfo infoTemp = SkImageInfo::MakeN32(80, 80, kPremul_SkAlphaType);
  bitmapTemp.allocPixels(infoTemp);

  SkCanvas canvas(bitmap);
  SkCanvas canvasTemp(bitmapTemp);
  SkPaint paint;
  SkRect r;

  // Set background as checker board
  SkShader *s = createChecker();
  paint.setShader(s);
  canvas.drawPaint(paint);
  paint.setShader(NULL);

  // Draw three rectangles of different colors
  SkPaint p;
  p.setARGB(255, 0, 255, 0);
  r.set(0, 0, 40, 40);
  canvasTemp.drawRect(r, p);
 
  p.setARGB(255, 255, 0, 0);
  r.offset(5, 5);
  canvasTemp.drawRect(r, p);
 
  p.setARGB(255, 0, 0, 255);
  r.offset(5, 5);
  canvasTemp.drawRect(r, p);

  SkSafeUnref(p.setColorFilter(createColorFilter()));
  canvas.drawBitmap(bitmapTemp, 10, 40, &p);

  {
    SkAutoLockPixels image_lock(bitmap);
    cairo_surface_t* surface = cairo_image_surface_create_for_data(
        (unsigned char*)bitmap.getPixels(), CAIRO_FORMAT_ARGB32,
        bitmap.width(), bitmap.height(), bitmap.rowBytes());
    cairo_surface_write_to_png(surface, "snapshot-cairo.png");
    cairo_surface_destroy(surface);
  }

  {
    SkAutoLockPixels image_lock(bitmap);
    if(!SkImageEncoder::EncodeFile("snapshot-skia.png", bitmap, SkImageEncoder::kPNG_Type, 100))
   		  fprintf(stderr, "Error when encoding file\n");
  }
 
  return 0;
}
