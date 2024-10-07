const express = require('express');
const { execFile } = require('child_process');
const app = express();
const port = 3001;
const cors = require('cors')

app.use(cors());

// CPU 정보를 제공하는 C 프로그램 실행
app.get('/cpu-info', (req, res) => {
    execFile('../send', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing C program: ${error}`);
            return res.status(500).send('Error fetching CPU info');
        }
        res.send(stdout); // C 프로그램의 출력값을 클라이언트로 전송
    });
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});