from setuptools import setup, Extension


metadata = dict(
    name='myjit',
    packages={
        'myjit',
    },
    ext_modules=[
         Extension(name='myjit._myjithook',
                   sources=['myjit/_myjithook.c'])
    ],
    license="BSD",
    )

setup(**metadata)
