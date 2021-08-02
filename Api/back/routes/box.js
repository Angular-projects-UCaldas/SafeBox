'use strict'

var express = require('express');
var BoxController = require('../controllers/boxController');
var api = express.Router();
var cors = require('cors');

api.use(cors());

api.post('/open', BoxController.openBox);
api.get('/status', BoxController.sendStatusBox);
api.post('/changepassword', BoxController.changePassword);
api.post('/changetime', BoxController.changeTime);

module.exports = api;