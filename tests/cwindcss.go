package cwindcss

// #cgo LDFLAGS: -L/usr/lib64 -ldl -lm
// #include <stdlib.h>
// #include "./cwindcss.h"
import "C"

import (
	"strings"
	"unsafe"
)

func ExtractCssClasses(html string) []string {
	C.cwind_init()
	defer C.cwind_destroy()

	cSize := C.size_t(0)
	cSizePtr := (*C.size_t)(unsafe.Pointer(&cSize))
	cClasses := C.cwind_extract_css_classes(C.CString(html), cSizePtr)
	classes := make([]string, 0, int(*cSizePtr))
	for i := 0; i < int(*cSizePtr); i++ {
		classes = append(classes,
			C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(cClasses)) + uintptr(i)*unsafe.Sizeof(*cClasses)))),
		)
	}
	C.free(unsafe.Pointer(cClasses))

	return classes
}

func ProcessUtilityClasses(html string) string {
	C.cwind_init()
	defer C.cwind_destroy()

	dingus := C.cwind_process_utility_classes(C.CString(html))

	defer C.free(unsafe.Pointer(dingus))
	return strings.Clone(C.GoString(dingus))
}
