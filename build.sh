FC=gfortran

KROME=krome
PROJECT=c_example
KROME_OUTPUT_DIR=krome/build_$PROJECT

set -x

# Run krome
(cd krome && python2 krome -test=hello -project=$PROJECT -interfaceC)

# Build krome objects (with custom Makefile)
cp c_example/krome_custom_Makefile $KROME_OUTPUT_DIR
make -f krome_custom_Makefile -C $KROME_OUTPUT_DIR gfortran cinterface

gcc -o run c_example/main.c $KROME_OUTPUT_DIR/*.o -I$KROME_OUTPUT_DIR -lm -lgfortran
