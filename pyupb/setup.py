#! /usr/bin/env python3

"""
# We must use setuptools, not distutils, because we need to use the
# namespace_packages option for the "google" package.
from setuptools import setup, Extension, find_packages

if __name__ == '__main__':
  setup(
      name='protobuf',
      version="0.0.1",
      description='Protocol Buffers',
      download_url='https://github.com/protocolbuffers/protobuf/releases',
      long_description="Protocol Buffers are Google's data interchange format",
      url='https://developers.google.com/protocol-buffers/',
      maintainer='protobuf@googlegroups.com',
      maintainer_email='protobuf@googlegroups.com',
      license='3-Clause BSD License',
      classifiers=[
        "Programming Language :: Python",
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        ],
      namespace_packages=['google'],
      packages=find_packages(
          exclude=[
              'import_test_package',
              'protobuf_distutils',
          ],
      ),
      #test_suite='google.protobuf.internal',
      #cmdclass={
      #    'clean': clean,
      #    'build_py': build_py,
      #    'test_conformance': test_conformance,
      #},
      #install_requires=install_requires,
      ext_modules=[
        Extension(
            "google.protobuf.pyext._message",
            [
                "py-upb.c",
            ],
            #glob.glob('google/protobuf/pyext/*.cc'),
            #include_dirs=[".", "../src"],
            #libraries=libraries,
            #extra_objects=extra_objects,
            #library_dirs=['../src/.libs'],
            #extra_compile_args = ['-fvisibility=hidden', '-ffunction-sections', '-fdata-sections'],
        ),
        #Extension(
        #    "google.protobuf.internal._api_implementation",
        #    glob.glob('google/protobuf/internal/api_implementation.cc'),
        #    extra_compile_args=extra_compile_args + ['-DPYTHON_PROTO2_CPP_IMPL_V2'],
        #),
      ]
  )
"""

from distutils.core import setup, Extension

ext = Extension('google.protobuf',
                sources = [
                  'descriptor.c',
                  'protobuf.c',
                  'py-upb.c'
                ],
                #extra_compile_args = ['-fvisibility=hidden', '-ffunction-sections', '-fdata-sections'],
                )

setup(
  name='protobuf',
  version="0.0.1",
  description='Protocol Buffers',
  download_url='https://github.com/protocolbuffers/protobuf/releases',
  long_description="Protocol Buffers are Google's data interchange format",
  url='https://developers.google.com/protocol-buffers/',
  maintainer='protobuf@googlegroups.com',
  maintainer_email='protobuf@googlegroups.com',
  license='3-Clause BSD License',
  classifiers=[
    "Programming Language :: Python",
    "Programming Language :: Python :: 2",
    "Programming Language :: Python :: 2.7",
    "Programming Language :: Python :: 3",
    "Programming Language :: Python :: 3.3",
    "Programming Language :: Python :: 3.4",
    "Programming Language :: Python :: 3.5",
    "Programming Language :: Python :: 3.6",
    "Programming Language :: Python :: 3.7",
    ],
  ext_modules = [ext],
)
