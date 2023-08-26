project('abend', 'c',
  license : 'GPLv3',
  default_options : ['warning_level=3'])

criterion = dependency('criterion')

gbuffer_test = executable('gbuffer', ['src/gbuffer.spec.c', 'src/gbuffer.c'], dependencies: criterion)
test('gbuffer', gbuffer_test)
