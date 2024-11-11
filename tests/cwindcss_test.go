package cwindcss_test

import (
	"cwindcss"
	"testing"
)

func TestExtractCssClasses(t *testing.T) {
	htmlStr := `
<div class="container">
  <p class="text-center intro p-1 p-[20px] pt-[69px] m-[12px]">Welcome!</p>
  <button class="btn btn-primary">Click me</button>
</div>`
	classes := cwindcss.ExtractCssClasses(htmlStr)
	t.Log("classes", classes)
}

func TestProcessUtilityClasses(t *testing.T) {
	htmlStr := `
<div class="container">
  <p class="text-center intro p-1 p-[20px] pt-[69px] m-[12px] mt-[200px]">Welcome!</p>
  <button class="btn btn-primary">Click me</button>
</div>`
	css := cwindcss.ProcessUtilityClasses(htmlStr)
	t.Log("css", css)
}
