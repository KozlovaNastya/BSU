"use strict"; 

/*
 * Load the model data for lab1. We load into DOM the
 * property lab1models.exampleModel a function that returns an object with the
 * following property:
 *    name:  A string with name.
 *
 * See README.md for information on how to access it.
 */
var lab1models;

if (lab1models === undefined) {
  lab1models = {};
}

lab1models.exampleModel = function () {
  return {
    name: "Anastasia",
  };
};
