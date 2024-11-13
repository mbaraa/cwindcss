<div align="center">
  <a href="https://dankmuzikk.com" target="_blank"><img src="https://github.com/mbaraa/cwindcss/blob/main/docs/logo.png" width="150" /></a>
  <h1>Cwind CSS</h1>
  <p>
    <strong>Tailwind CSS, But in C</strong>
  </p>
  <p>
    <a href="https://github.com/mbaraa/cwindcss/actions/workflows/tests.yml">
      <img src="https://github.com/mbaraa/cwindcss/actions/workflows/tests.yml/badge.svg" alt="Tests">
    </a>
  </p>
</div>

# About

**Cwind CSS** A [Tailwind CSS](https://tailwindcss.com/) port in C, just for the fun of it.

_Note: this is a fling side-project that could die anytime so don't get your hopes up._

# Installation:

```bash
git clone https://github.com/mbaraa/cwindcss
cd ctemplate
make
sudo make install
```

# Usage:

1. Include the header

```c
#include <cwindcss.h>
```

2. Go nuts.

# Roadmap

## Layout

- [x] Sizing: w-, h-, min-w-, min-h-, max-w-, max-h- (width, height, min/max width/height)
- [x] Spacing: p-, m-, space-x-, space-y- (padding, margin, horizontal/vertical spacing)
- [x] Positioning: static, fixed, absolute, relative, sticky, top-, right-, bottom-, left-, inset-, z- (positioning and z-index)
- [ ] Display: block, inline-block, inline, flex, grid, table, hidden (display modes)
- [ ] Flexbox: flex-row, flex-col, flex-wrap, flex-nowrap, flex-grow, flex-shrink, order-, justify-, items-, content-, self- (flexbox properties)
- [ ] Grid: grid-cols-, grid-rows-, gap-, row-span-, col-span- (grid layout properties)
- [ ] Tables: table-auto, table-fixed (table layout)
- [ ] Box Alignment: float-, clear- (float and clear)

## Typography

- [ ] Font Family: font- (font families)
- [ ] Font Size: text- (font sizes)
- [ ] Font Weight: font- (font weights - e.g., font-bold, font-extrabold)
- [ ] Font Style: italic, not-italic
- [ ] Line Height: leading-
- [ ] Letter Spacing: tracking-
- [ ] Text Alignment: text-left, text-center, text-right, text-justify
- [ ] Text Color: text- (text colors)
- [ ] Text Decoration: underline, line-through, no-underline
- [ ] Text Transform: uppercase, lowercase, capitalize, normal-case
- [ ] Vertical Alignment: align- (vertical alignment)
- [ ] Whitespace: whitespace- (e.g., whitespace-nowrap)
- [ ] Word Break: break- (e.g., break-words)

## Backgrounds

- [ ] Background Color: bg- (background colors)
- [ ] Background Image: bg- (e.g., bg-none, bg-gradient-to-r)
- [ ] Background Position: bg- (e.g., bg-bottom, bg-center)
- [ ] Background Size: bg- (e.g., bg-cover, bg-contain)
- [ ] Background Repeat: bg- (e.g., bg-repeat, bg-no-repeat)
- [ ] Background Attachment: bg- (e.g., bg-fixed, bg-scroll)

## Borders

- [ ] Border Width: border-, border-t-, border-r-, border-b-, border-l- (border widths for all sides or individual sides)
- [ ] Border Color: border- (border colors)
- [ ] Border Style: border-solid, border-dashed, border-dotted, border-double, border-none
- [ ] Border Radius: rounded-, rounded-t-, rounded-r-, rounded-b-, rounded-l- (border radius for all corners or individual corners)

## Effects

- [ ] Shadows: shadow-, shadow-inner (box shadows)
- [ ] Opacity: opacity-
- [ ] Transitions: transition-, transition-all, transition-colors, etc. (transition properties and durations)
- [ ] Transforms: transform, rotate-, scale-, translate-x-, translate-y-, skew-x-, skew-y- (transform properties)

## Interactivity

- [ ] Appearance: appearance-none (removes default browser styles)
- [ ] Cursor: cursor- (e.g., cursor-pointer, cursor-not-allowed)
- [ ] Outline: outline-, outline-none
- [ ] Pointer Events: pointer-events- (e.g., pointer-events-none)
- [ ] Resize: resize- (e.g., resize-none, resize-y)
- [ ] User Select: select- (e.g., select-none, select-text)

## SVG

- [ ] Fill: fill- (fill colors)
- [ ] Stroke: stroke- (stroke colors)
- [ ] Stroke Width: stroke- (stroke widths)

## Accessibility

- [ ] sr-only: Hides an element visually, but keeps it available to screen readers. Useful for accessibility.
- [ ] not-sr-only: The opposite of sr-only, ensures an element is visible.

## Breakpoint Prefixes: To make a utility apply only at specific screen sizes, you add a prefix:

- [ ] sm: (small screens - typically 640px and wider)
- [ ] md: (medium screens - 768px)
- [ ] lg: (large screens - 1024px)
- [ ] xl: (extra-large screens - 1280px)
- [ ] 2xl: (2x extra-large screens - 1536px)

## State Modifiers (Pseudo-classes)

- Hover:

* [ ] hover: (styles applied on mouse hover)
* [ ] Focus: focus: (styles when an element has focus)
* [ ] Active: active: (styles when an element is being interacted with – e.g., a button being clicked)
* [ ] Visited: visited: (styles for visited links)
* [ ] Disabled: disabled: (styles for disabled elements)
* [ ] First-child, Last-child, etc.: first:, last:, only:, odd:, even: (styles based on element position within a group)
* [ ] Group Modifiers: group-hover:, group-focus: (styles applied to an element within a parent with the group class when the parent is hovered or focused)
* [ ] Focus-within: focus-within: (styles applied to a parent element when any child element has focus)

- Other Modifiers

* [ ] Dark Mode: dark: (styles applied when the user has dark mode enabled)
* [ ] Motion-safe/Motion-reduce: motion-safe: and motion-reduce: (control animations based on user preferences)
* [ ] Print: print: (styles applied when printing the page)
* [ ] Important: ! (adds !important to the generated CSS)
* [ ] Arbitrary values: [] (allows you to use custom values not defined in your Tailwind config, e.g., w-[345px])
* [ ] Attribute selectors: [attribute="value"]: (apply styles based on attributes, e.g., [data-open="true"])

## Form Element Modifiers:

These apply to form elements like input fields, checkboxes, and radio buttons:

- [ ] checked: Styles for checked checkboxes/radio buttons.
- [ ] disabled: Styles for disabled form elements.
- [ ] indeterminate: Styles for checkboxes in an indeterminate state.
- [ ] invalid: Styles for invalid form elements.
- [ ] placeholder-shown: Styles when an input has placeholder text visible.
- [ ] read-only: Styles for read-only form elements.
- [ ] required: Styles for required form elements.

## Child Modifiers

These let you style elements based on their position within a parent:

- [ ] first: Styles the first child element.
- [ ] last: Styles the last child element.
- [ ] only: Styles an only child element.
- [ ] odd: Styles odd-numbered child elements.
- [ ] even: Styles even-numbered child elements.

## Other Modifiers:

- [ ] open: Styles for elements that are currently open (like a dropdown menu).
- [ ] first-of-type, last-of-type, only-of-type: Similar to first:, last:, and only:, but these target elements based on their type within a parent (e.g., the first paragraph, the last image).
- [ ] target: Applies styles to the element that is the target of a link (e.g., if you have an in-page link to a heading, this lets you style that heading when the link is clicked).
- [ ] default: Styles form elements that are selected by default (e.g., a radio button).
- [ ] optional: Styles form elements that are not required.
- [ ] valid: Styles valid form elements.
- [ ] in-range, out-of-range: Styles form elements with numeric values that fall within or outside a specified range.
- [ ] autofill: Styles form elements that have been autofilled by the browser.
- [ ] -class-name: Sets the numerical value of the class to negative, (e.g., -p-[12px] becomes padding: -12px;).
- [ ] !class-name: Sets the value as important, (e.g., !p-[12px] becomes padding: 12px !important;).

## Units

CSS has a wide variety of units for expressing different types of values. Here's a breakdown of some common categories and their units:

- Absolute Units: These units have a fixed size, regardless of the context.

* [x] px: Pixels. This is the most common unit for screen displays.
* [x] in: Inches.
* [x] cm: Centimeters.
* [x] mm: Millimeters.
* [x] pt: Points (1pt = 1/72 of an inch).
* [x] pc: Picas (1pc = 12pt).

- Relative Units: These units are relative to another value, such as the font size or viewport dimensions.

* [x] em: Relative to the font size of the element.
* [x] rem: Relative to the font size of the root element (usually the <html> element).
* [x] %: Percentage.
* [x] ex: Relative to the x-height of the element's font.
* [x] ch: Relative to the width of the "0" character in the element's font.
* [x] vw: Viewport width (1vw = 1% of the viewport width).
* [x] vh: Viewport height (1vh = 1% of the viewport height).
* [x] vmin: Viewport minimum (1vmin = 1% of the viewport's smaller dimension).
* [x] vmax: Viewport maximum (1vmax = 1% of the viewport's larger dimension).

- Angle Units:

* [x] deg: Degrees.
* [x] rad: Radians.
* [x] grad: Gradians.
* [x] turn: Turns (1turn = 360deg).

- Time Units:

* [x] s: Seconds.
* [x] ms: Milliseconds.

- Resolution Units:

* [x] dpi: Dots per inch.
* [x] dpcm: Dots per centimeter.
* [x] dppx: Dots per pixel.

- Frequency Units:

* [x] Hz: Hertz.
* [x] kHz: Kilohertz.

# Acknowledgements

- This project is not affiliated with [Tailwind CSS](https://tailwindcss.com).
- The logo was made by [@DrSensor](https://github.com/DrSensor)

---

Made with 🧉 by [Baraa Al-Masri](https://mbaraa.com)
