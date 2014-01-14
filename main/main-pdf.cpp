#include "SkPaint.h"
#include "SkData.h"
#include "SkCanvas.h"
#include "SkPDFDevice.h"
#include "SkPDFDocument.h"
#include "SkPDFCanon.h"
#include "SkDocument.h"

#include <stdio.h>

int main(int argc, char** argv) {
    const SkISize pageSize = SkISize::Make(100, 100);
    SkPDFCanon fCanon;
    SkAutoTUnref<SkPDFDevice> dev(SkPDFDevice::Create(pageSize,
						      SK_ScalarDefaultRasterDPI,
						      &fCanon));

    SkCanvas c(dev);
    SkPaint paint;
    paint.setColor(SK_ColorBLACK);
    paint.setTextSize(SkIntToScalar(20));

    paint.setFakeBoldText(false);
    const uint16_t text = 'a';
    c.drawText(&text, 1, SkIntToScalar(0), SkIntToScalar(50), paint);

    paint.setFakeBoldText(true);
    c.drawText(&text, 1, SkIntToScalar(20), SkIntToScalar(50), paint);

    paint.setFakeBoldText(false);
    c.drawLine(SkIntToScalar(0), SkIntToScalar(50), SkIntToScalar(100), SkIntToScalar(50), paint);
    paint.setColor(SK_ColorRED);
    c.drawText(&text, 1, SkIntToScalar(0), SkIntToScalar(50), paint);

    SkPDFDocument doc;
    doc.appendPage(dev);

    SkDynamicMemoryWStream stream;
    doc.emitPDF(&stream);
    SkAutoDataUnref data(stream.copyToData());
    FILE* fp = fopen("out.pdf", "w");
    fwrite(data->data(), 1, stream.getOffset(), fp);
    fclose(fp);
    return 0;
}
