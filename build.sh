FC=gfortran

KROME=krome
PROJECT=c_example
KROME_OUTPUT_DIR=krome/build_$PROJECT
LIBNAME=krome

set -x

(cd krome && python2 krome -test=hello -project=$PROJECT -interfaceC)

make -C $KROME_OUTPUT_DIR cinterface gfortran
rm $KROME_OUTPUT_DIR/test.o # we don't want this in our shared library
$FC $KROME_OUTPUT_DIR/*.o -o $KROME_OUTPUT_DIR/lib${LIBNAME}.so -shared -llapack

gcc -o run c_example/main.c -I$KROME_OUTPUT_DIR -L$KROME_OUTPUT_DIR -l$LIBNAME -lm -lgfortran

