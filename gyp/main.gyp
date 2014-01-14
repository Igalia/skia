{
  'targets': [
    {
      'target_name': 'main',
      'type': 'executable',
      'include_dirs' : [
        '../include/core',
        '../include/config',
        '../include/effects',
        '../include/images',
	'../src/images',
      ],
      'sources': [
        '../main/main.cpp',
      ],
      'dependencies': [
        'skia_lib.gyp:skia_lib',
        'effects.gyp:effects',
        'images.gyp:images',
        'views.gyp:views',
        'pdf.gyp:pdf',
        'gpu.gyp:skgpu',
      ],
      'ldflags': [
        '-lcairo',
	'-lpng',
      ],
    },
    {
      'target_name': 'main-skp',
      'type': 'executable',
      'include_dirs' : [
        '../include/core',
        '../include/config',
        '../include/effects',
        '../include/images',
	'../src/images',
      ],
      'sources': [
        '../main/main-skp.cpp',
      ],
      'dependencies': [
        'skia_lib.gyp:skia_lib',
        'effects.gyp:effects',
        'images.gyp:images',
        'views.gyp:views',
      ],
      'ldflags': [
	'-lpng',
      ],
    },
    {
      'target_name': 'main-pdf',
      'type': 'executable',
      'include_dirs' : [
        '../include/core',
        '../include/config',
        '../src/pdf',
        '../src/core',
      ],
      'sources': [
        '../main/main-pdf.cpp',
      ],
      'dependencies': [
        'skia_lib.gyp:skia_lib',
        'pdf.gyp:pdf',
      ],
      'ldflags': [
        '-lpng',
      ],
    },
    {
      'target_name': 'main-font',
      'type': 'executable',
      'include_dirs' : [
        '../include/core',
        '../include/config',
        '../src/pdf',
        '../src/core',
      ],
      'sources': [
        '../main/main-font.cpp',
      ],
      'dependencies': [
        'skia_lib.gyp:skia_lib',
        'pdf.gyp:pdf',
      ],
      'ldflags': [
	
      ],
    },
    {
      'target_name': 'main-gl',
      'type': 'executable',
      'include_dirs' : [
        '../include/core',
        '../include/config',
        '../include/effects',
        '../include/images',
        '../src/gpu',
        '../include/gpu/gl',
	'../src/images',
      ],
      'sources': [
        '../main/main-gl.cpp',
      ],
      'dependencies': [
        'skia_lib.gyp:skia_lib',
        'effects.gyp:effects',
        'images.gyp:images',
        'views.gyp:views',
      ],
      'ldflags': [
        '-lcairo',
		'-lpng',
		'-lglut',
		'-lGLU',
		'-lGLEW',
		'-lglfw',
      ],
    },
  ],
}
