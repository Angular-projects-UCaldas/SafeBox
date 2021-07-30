'use strict'

const express = require('express');
const app = express();

app.use(express.urlencoded({ extended: false }));

app.use(express.json());

//var SerialController = require('./controllers/serialController');
var BoxRoutes = require('./routes/box');

app.use('/api', BoxRoutes);
app.use('/', (req, res) => {
    res.status(200).send('Welcome to the API!');
});

module.exports = app;
