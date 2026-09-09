"use strict"; 

/*
 * Load the model data for lab1. We load into the property
 * lab1models.regionsModel a function that returns an array of strings with the
 * names of the regions.
 *
 * 
 */

var lab1models;

if (lab1models === undefined) {
  lab1models = {};
}

lab1models.regionsModel = function () {
  return [
    "Брестская",
    "Витебская",
    "Гомельская",
    "Гродненская",
    "Минская",
    "Могилевская",
    "Минск",    
  ];
};
