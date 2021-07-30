'use strict'

var express = require('express');
var BoxController = require('../controllers/boxController');
var api = express.Router();

//api.get('/serial', BoxController.getBox);
api.post('/serial',BoxController.getBox);

module.exports = api;