#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <GL/glfw.h>

#include "GrContext.h"
#include "GrRenderTarget.h"
#include "GrGLInterface.h"
#include "SkGpuDevice.h"
#include "SkCanvas.h"
#include "SkGraphics.h"

int main( int ac,char** av )
{
	SkAutoGraphics ag;
	int window_width = 800,
	    window_height = 600;

	// Create window by using GLFW framework
	if( glfwInit() == GL_FALSE )
	{
		printf("Could not initialize GLFW. Aborting.\n" );
		exit(1);
	}

	if (glfwOpenWindow(window_width, window_height, 8,8,8,8,24,8, GLFW_WINDOW) == GL_FALSE)
	{
		printf("Could not open GLFW window. Aborting.\n" );
		exit(2);
	}

	const GrGLInterface* fGL = GrGLCreateNativeInterface();
	GrContext* fGrContext = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)fGL );
	if (!fGrContext)
	{
		printf("fGrContext was null\n");
		exit(3);
	}


	GrRenderTarget* fGrRenderTarget;

	GrBackendRenderTargetDesc desc;
	desc.fWidth = window_width;
	desc.fHeight = window_height;
	desc.fConfig = kSkia8888_GrPixelConfig;
	fGrRenderTarget = fGrContext->wrapBackendRenderTarget(desc);
	const SkSurfaceProps gProps = SkSurfaceProps(SkSurfaceProps::kLegacyFontHost_InitType);
	unsigned flags = 0;
	// Create Canvas
	SkGpuDevice *gpuDevice = SkGpuDevice::Create(fGrRenderTarget, &gProps, flags);
	SkCanvas *gpuCanvas = new SkCanvas(gpuDevice);

	glfwSetWindowTitle( "Skia GLFW Test" );

	do {
		// Draw a red background with a gray, semi-transparent circle in the top left corner.
		gpuCanvas->drawColor(SK_ColorRED);
		SkRect r(SkRect::MakeWH(200,200));
		SkPaint p;
		p.setARGB( 200,100,100,100 );
		gpuCanvas->drawOval(r, p);

		// Finished drawing, ready to present, must tell GrContext to flush itself. This 
		// doesn't call glFlush, it just flushes deferred draws in GrContext to OpenGL.
		fGrContext->flush(false);
		glfwSwapBuffers();

		// Avoid refreshing all the time. This is just a hack
		sleep(1);
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}
