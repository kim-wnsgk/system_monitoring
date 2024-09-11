const express = require('express');
const { exec } = require('child_process');

const app = express();

app.set('port', process.env.PORT || 3000);

app.get('/', (req, res) => {
    res.send('Hello World');
});

app.get('/cpu', (req, res) => {
    exec('./cpuUsage', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing CPU usage: ${error.message}`);
            return res.status(500).send('Error retrieving CPU usage');
        }

        if (stderr) {
            console.error(`stderr: ${stderr}`);
        }

        res.send({ cpuUsage: stdout.trim() });
    });
});

app.get('/mem', (req, res) => {
    res.send('Hello World');
});

app.listen(app.get('port'), () => {
    console.log('Server is running on port', app.get('port'));
});