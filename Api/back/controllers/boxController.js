'use strict'

const serialPort = require('serialport');

const portSerial = new serialPort('COM2', {baudRate: 9600});

const parser = new serialPort.parsers.Readline();

portSerial.pipe(parser);

let status = [];

parser.on('data', (data) => {
    console.log(data);
    status.push({"status" : data});
});


const sendStatusBox = (req, res) => {

    res.status(200).send({data: status});
};

const openBox = (req, res) => {
    portSerial.write("1");
    res.status(200).send({message: "Box Opened"});
}

const changePassword = (req, res) => {
    portSerial.write(req.body.data);
    res.status(200).send({message: "Password Changed"});
}

const changeTime = (req, res) => {
    portSerial.write(req.body.data);
    res.status(200).send({message: "Time Changed"});
}

module.exports = {
    openBox,
    sendStatusBox,
    changePassword,
    changeTime
};