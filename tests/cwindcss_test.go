package cwindcss_test

import (
	"cwindcss"
	"testing"
)

func Test_ExtractCssClasses_ReturnsUniqueClasses(t *testing.T) {
	htmlStr := `<div class="flex justify-center items-center flex-col md:flex-row gap-1 h-min">
		<img
			src="/static/images/logo.webp"
			class="w-[55px] rounded-md flex"
		/>
		<h1 class="text-3xl lg:text-2xl md:hidden lg:block">DankMuzikk</h1>
	</div>`
	classesFreq := map[string]int32{}
	classes := cwindcss.ExtractCssClasses(htmlStr)
	for _, class := range classes {
		classesFreq[class]++
		if classesFreq[class] > 1 {
			t.Fatalf("%s has %d occurrences\n", class, classesFreq[class])
		}
	}
}

func Test_ExtractCssClasses_ReturnsEmptyArray_WhenNoClassesAreProvided(t *testing.T) {
	classes := cwindcss.ExtractCssClasses("")
	if len(classes) != 0 {
		t.Fatalf("expected length to be 0, but got %d\n", len(classes))
	}
}

func Test_ProcessUtilityClasses_Returns_UniqueCssClassesOfTheGivenUtilityClasses(t *testing.T) {
	htmlStr := `
<div class="container">
  <p class="text-center intro p-1 p-[20px] pt-[69px] m-[12px] mt-[200px] pb-[420px]">Welcome!</p>
  <button class="btn btn-primary">Click me</button>
</div>`
	css := cwindcss.ProcessUtilityClasses(htmlStr)
	if css != `.p20px {padding: 20px;} .pt69px {padding-top: 69px;} .m12px {margin: 12px;} .mt200px {margin-top: 200px;} .pb420px {padding-bottom: 420px;}` {
		t.Fatal("output css is invalid")
	}
}
