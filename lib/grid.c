#include "grid.h"
#include "utility_classes.h"

void init_grid_classes() {
  add_util_class("grid-rows-1",
                 ".%s {grid-template-rows: repeat(1, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-1",
      ".%s {grid-template-rows: repeat(1, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-2",
                 ".%s {grid-template-rows: repeat(2, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-2",
      ".%s {grid-template-rows: repeat(2, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-3",
                 ".%s {grid-template-rows: repeat(3, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-3",
      ".%s {grid-template-rows: repeat(3, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-4",
                 ".%s {grid-template-rows: repeat(4, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-4",
      ".%s {grid-template-rows: repeat(4, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-5",
                 ".%s {grid-template-rows: repeat(5, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-5",
      ".%s {grid-template-rows: repeat(5, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-6",
                 ".%s {grid-template-rows: repeat(6, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-6",
      ".%s {grid-template-rows: repeat(6, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-7",
                 ".%s {grid-template-rows: repeat(7, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-7",
      ".%s {grid-template-rows: repeat(7, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-8",
                 ".%s {grid-template-rows: repeat(8, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-8",
      ".%s {grid-template-rows: repeat(8, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-9",
                 ".%s {grid-template-rows: repeat(9, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-9",
      ".%s {grid-template-rows: repeat(9, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-10",
                 ".%s {grid-template-rows: repeat(10, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-10",
      ".%s {grid-template-rows: repeat(10, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-11",
                 ".%s {grid-template-rows: repeat(11, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-11",
      ".%s {grid-template-rows: repeat(11, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-12",
                 ".%s {grid-template-rows: repeat(12, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-rows-12",
      ".%s {grid-template-rows: repeat(12, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-rows-none", ".%s {grid-template-rows: none;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-rows-none",
                 ".%s {grid-template-rows: none !important;}", NO_REPLACEMENT);
  add_util_class("grid-rows-subgrid", ".%s {grid-template-rows: subgrid;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-rows-subgrid",
                 ".%s {grid-template-rows: subgrid !important;}",
                 NO_REPLACEMENT);

  add_util_class("grid-cols-1",
                 ".%s {grid-template-columns: repeat(1, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-1",
      ".%s {grid-template-columns: repeat(1, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-2",
                 ".%s {grid-template-columns: repeat(2, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-2",
      ".%s {grid-template-columns: repeat(2, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-3",
                 ".%s {grid-template-columns: repeat(3, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-3",
      ".%s {grid-template-columns: repeat(3, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-4",
                 ".%s {grid-template-columns: repeat(4, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-4",
      ".%s {grid-template-columns: repeat(4, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-5",
                 ".%s {grid-template-columns: repeat(5, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-5",
      ".%s {grid-template-columns: repeat(5, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-6",
                 ".%s {grid-template-columns: repeat(6, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-6",
      ".%s {grid-template-columns: repeat(6, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-7",
                 ".%s {grid-template-columns: repeat(7, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-7",
      ".%s {grid-template-columns: repeat(7, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-8",
                 ".%s {grid-template-columns: repeat(8, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-8",
      ".%s {grid-template-columns: repeat(8, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-9",
                 ".%s {grid-template-columns: repeat(9, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-9",
      ".%s {grid-template-columns: repeat(9, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-10",
                 ".%s {grid-template-columns: repeat(10, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-10",
      ".%s {grid-template-columns: repeat(10, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-11",
                 ".%s {grid-template-columns: repeat(11, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-11",
      ".%s {grid-template-columns: repeat(11, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-12",
                 ".%s {grid-template-columns: repeat(12, minmax(0, 1fr));}",
                 NO_REPLACEMENT);
  add_util_class(
      "!grid-cols-12",
      ".%s {grid-template-columns: repeat(12, minmax(0, 1fr)) !important;}",
      NO_REPLACEMENT);
  add_util_class("grid-cols-none", ".%s {grid-template-columns: none;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-cols-none",
                 ".%s {grid-template-columns: none !important;}",
                 NO_REPLACEMENT);
  add_util_class("grid-cols-subgrid", ".%s {grid-template-columns: subgrid;}",
                 NO_REPLACEMENT);
  add_util_class("!grid-cols-subgrid",
                 ".%s {grid-template-columns: subgrid !important;}",
                 NO_REPLACEMENT);

  add_util_class("row-auto", ".%s {grid-row: auto;}", NO_REPLACEMENT);
  add_util_class("!row-auto", ".%s {grid-row: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-1", ".%s {grid-row: span 1 / span 1;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-1", ".%s {grid-row: span 1 / span 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-2", ".%s {grid-row: span 2 / span 2;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-2", ".%s {grid-row: span 2 / span 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-3", ".%s {grid-row: span 3 / span 3;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-3", ".%s {grid-row: span 3 / span 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-4", ".%s {grid-row: span 4 / span 4;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-4", ".%s {grid-row: span 4 / span 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-5", ".%s {grid-row: span 5 / span 5;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-5", ".%s {grid-row: span 5 / span 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-6", ".%s {grid-row: span 6 / span 6;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-6", ".%s {grid-row: span 6 / span 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-7", ".%s {grid-row: span 7 / span 7;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-7", ".%s {grid-row: span 7 / span 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-8", ".%s {grid-row: span 8 / span 8;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-8", ".%s {grid-row: span 8 / span 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-9", ".%s {grid-row: span 9 / span 9;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-9", ".%s {grid-row: span 9 / span 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-10", ".%s {grid-row: span 10 / span 10;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-10",
                 ".%s {grid-row: span 10 / span 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-11", ".%s {grid-row: span 11 / span 11;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-11",
                 ".%s {grid-row: span 11 / span 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-12", ".%s {grid-row: span 12 / span 12;}",
                 NO_REPLACEMENT);
  add_util_class("!row-span-12",
                 ".%s {grid-row: span 12 / span 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-span-full", ".%s {grid-row: 1 / -1;}", NO_REPLACEMENT);
  add_util_class("!row-span-full", ".%s {grid-row: 1 / -1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-1", ".%s {grid-row-start: 1;}", NO_REPLACEMENT);
  add_util_class("!row-start-1", ".%s {grid-row-start: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-2", ".%s {grid-row-start: 2;}", NO_REPLACEMENT);
  add_util_class("!row-start-2", ".%s {grid-row-start: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-3", ".%s {grid-row-start: 3;}", NO_REPLACEMENT);
  add_util_class("!row-start-3", ".%s {grid-row-start: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-4", ".%s {grid-row-start: 4;}", NO_REPLACEMENT);
  add_util_class("!row-start-4", ".%s {grid-row-start: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-5", ".%s {grid-row-start: 5;}", NO_REPLACEMENT);
  add_util_class("!row-start-5", ".%s {grid-row-start: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-6", ".%s {grid-row-start: 6;}", NO_REPLACEMENT);
  add_util_class("!row-start-6", ".%s {grid-row-start: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-7", ".%s {grid-row-start: 7;}", NO_REPLACEMENT);
  add_util_class("!row-start-7", ".%s {grid-row-start: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-8", ".%s {grid-row-start: 8;}", NO_REPLACEMENT);
  add_util_class("!row-start-8", ".%s {grid-row-start: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-9", ".%s {grid-row-start: 9;}", NO_REPLACEMENT);
  add_util_class("!row-start-9", ".%s {grid-row-start: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-10", ".%s {grid-row-start: 10;}", NO_REPLACEMENT);
  add_util_class("!row-start-10", ".%s {grid-row-start: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-11", ".%s {grid-row-start: 11;}", NO_REPLACEMENT);
  add_util_class("!row-start-11", ".%s {grid-row-start: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-12", ".%s {grid-row-start: 12;}", NO_REPLACEMENT);
  add_util_class("!row-start-12", ".%s {grid-row-start: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-13", ".%s {grid-row-start: 13;}", NO_REPLACEMENT);
  add_util_class("!row-start-13", ".%s {grid-row-start: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-start-auto", ".%s {grid-row-start: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!row-start-auto", ".%s {grid-row-start: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-1", ".%s {grid-row-end: 1;}", NO_REPLACEMENT);
  add_util_class("!row-end-1", ".%s {grid-row-end: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-2", ".%s {grid-row-end: 2;}", NO_REPLACEMENT);
  add_util_class("!row-end-2", ".%s {grid-row-end: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-3", ".%s {grid-row-end: 3;}", NO_REPLACEMENT);
  add_util_class("!row-end-3", ".%s {grid-row-end: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-4", ".%s {grid-row-end: 4;}", NO_REPLACEMENT);
  add_util_class("!row-end-4", ".%s {grid-row-end: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-5", ".%s {grid-row-end: 5;}", NO_REPLACEMENT);
  add_util_class("!row-end-5", ".%s {grid-row-end: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-6", ".%s {grid-row-end: 6;}", NO_REPLACEMENT);
  add_util_class("!row-end-6", ".%s {grid-row-end: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-7", ".%s {grid-row-end: 7;}", NO_REPLACEMENT);
  add_util_class("!row-end-7", ".%s {grid-row-end: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-8", ".%s {grid-row-end: 8;}", NO_REPLACEMENT);
  add_util_class("!row-end-8", ".%s {grid-row-end: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-9", ".%s {grid-row-end: 9;}", NO_REPLACEMENT);
  add_util_class("!row-end-9", ".%s {grid-row-end: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-10", ".%s {grid-row-end: 10;}", NO_REPLACEMENT);
  add_util_class("!row-end-10", ".%s {grid-row-end: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-11", ".%s {grid-row-end: 11;}", NO_REPLACEMENT);
  add_util_class("!row-end-11", ".%s {grid-row-end: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-12", ".%s {grid-row-end: 12;}", NO_REPLACEMENT);
  add_util_class("!row-end-12", ".%s {grid-row-end: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-13", ".%s {grid-row-end: 13;}", NO_REPLACEMENT);
  add_util_class("!row-end-13", ".%s {grid-row-end: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("row-end-auto", ".%s {grid-row-end: auto;}", NO_REPLACEMENT);
  add_util_class("!row-end-auto", ".%s {grid-row-end: auto !important;}",
                 NO_REPLACEMENT);

  add_util_class("col-auto", ".%s {grid-column: auto;}", NO_REPLACEMENT);
  add_util_class("!col-auto", ".%s {grid-column: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-1", ".%s {grid-column: span 1 / span 1;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-1",
                 ".%s {grid-column: span 1 / span 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-2", ".%s {grid-column: span 2 / span 2;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-2",
                 ".%s {grid-column: span 2 / span 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-3", ".%s {grid-column: span 3 / span 3;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-3",
                 ".%s {grid-column: span 3 / span 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-4", ".%s {grid-column: span 4 / span 4;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-4",
                 ".%s {grid-column: span 4 / span 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-5", ".%s {grid-column: span 5 / span 5;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-5",
                 ".%s {grid-column: span 5 / span 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-6", ".%s {grid-column: span 6 / span 6;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-6",
                 ".%s {grid-column: span 6 / span 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-7", ".%s {grid-column: span 7 / span 7;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-7",
                 ".%s {grid-column: span 7 / span 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-8", ".%s {grid-column: span 8 / span 8;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-8",
                 ".%s {grid-column: span 8 / span 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-9", ".%s {grid-column: span 9 / span 9;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-9",
                 ".%s {grid-column: span 9 / span 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-10", ".%s {grid-column: span 10 / span 10;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-10",
                 ".%s {grid-column: span 10 / span 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-11", ".%s {grid-column: span 11 / span 11;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-11",
                 ".%s {grid-column: span 11 / span 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-12", ".%s {grid-column: span 12 / span 12;}",
                 NO_REPLACEMENT);
  add_util_class("!col-span-12",
                 ".%s {grid-column: span 12 / span 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-span-full", ".%s {grid-column: 1 / -1;}", NO_REPLACEMENT);
  add_util_class("!col-span-full", ".%s {grid-column: 1 / -1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-1", ".%s {grid-column-start: 1;}", NO_REPLACEMENT);
  add_util_class("!col-start-1", ".%s {grid-column-start: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-2", ".%s {grid-column-start: 2;}", NO_REPLACEMENT);
  add_util_class("!col-start-2", ".%s {grid-column-start: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-3", ".%s {grid-column-start: 3;}", NO_REPLACEMENT);
  add_util_class("!col-start-3", ".%s {grid-column-start: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-4", ".%s {grid-column-start: 4;}", NO_REPLACEMENT);
  add_util_class("!col-start-4", ".%s {grid-column-start: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-5", ".%s {grid-column-start: 5;}", NO_REPLACEMENT);
  add_util_class("!col-start-5", ".%s {grid-column-start: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-6", ".%s {grid-column-start: 6;}", NO_REPLACEMENT);
  add_util_class("!col-start-6", ".%s {grid-column-start: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-7", ".%s {grid-column-start: 7;}", NO_REPLACEMENT);
  add_util_class("!col-start-7", ".%s {grid-column-start: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-8", ".%s {grid-column-start: 8;}", NO_REPLACEMENT);
  add_util_class("!col-start-8", ".%s {grid-column-start: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-9", ".%s {grid-column-start: 9;}", NO_REPLACEMENT);
  add_util_class("!col-start-9", ".%s {grid-column-start: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-10", ".%s {grid-column-start: 10;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-10", ".%s {grid-column-start: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-11", ".%s {grid-column-start: 11;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-11", ".%s {grid-column-start: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-12", ".%s {grid-column-start: 12;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-12", ".%s {grid-column-start: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-13", ".%s {grid-column-start: 13;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-13", ".%s {grid-column-start: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-start-auto", ".%s {grid-column-start: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!col-start-auto", ".%s {grid-column-start: auto !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-1", ".%s {grid-column-end: 1;}", NO_REPLACEMENT);
  add_util_class("!col-end-1", ".%s {grid-column-end: 1 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-2", ".%s {grid-column-end: 2;}", NO_REPLACEMENT);
  add_util_class("!col-end-2", ".%s {grid-column-end: 2 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-3", ".%s {grid-column-end: 3;}", NO_REPLACEMENT);
  add_util_class("!col-end-3", ".%s {grid-column-end: 3 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-4", ".%s {grid-column-end: 4;}", NO_REPLACEMENT);
  add_util_class("!col-end-4", ".%s {grid-column-end: 4 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-5", ".%s {grid-column-end: 5;}", NO_REPLACEMENT);
  add_util_class("!col-end-5", ".%s {grid-column-end: 5 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-6", ".%s {grid-column-end: 6;}", NO_REPLACEMENT);
  add_util_class("!col-end-6", ".%s {grid-column-end: 6 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-7", ".%s {grid-column-end: 7;}", NO_REPLACEMENT);
  add_util_class("!col-end-7", ".%s {grid-column-end: 7 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-8", ".%s {grid-column-end: 8;}", NO_REPLACEMENT);
  add_util_class("!col-end-8", ".%s {grid-column-end: 8 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-9", ".%s {grid-column-end: 9;}", NO_REPLACEMENT);
  add_util_class("!col-end-9", ".%s {grid-column-end: 9 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-10", ".%s {grid-column-end: 10;}", NO_REPLACEMENT);
  add_util_class("!col-end-10", ".%s {grid-column-end: 10 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-11", ".%s {grid-column-end: 11;}", NO_REPLACEMENT);
  add_util_class("!col-end-11", ".%s {grid-column-end: 11 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-12", ".%s {grid-column-end: 12;}", NO_REPLACEMENT);
  add_util_class("!col-end-12", ".%s {grid-column-end: 12 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-13", ".%s {grid-column-end: 13;}", NO_REPLACEMENT);
  add_util_class("!col-end-13", ".%s {grid-column-end: 13 !important;}",
                 NO_REPLACEMENT);
  add_util_class("col-end-auto", ".%s {grid-column-end: auto;}",
                 NO_REPLACEMENT);
  add_util_class("!col-end-auto", ".%s {grid-column-end: auto !important;}",
                 NO_REPLACEMENT);
}
