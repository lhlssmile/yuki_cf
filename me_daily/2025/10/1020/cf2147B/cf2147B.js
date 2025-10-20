const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

let lines = [];
let currentLine = 0;

function input() { return lines[currentLine++]; }
function nextInt() { return parseInt(input()); }
function nextIntArray() { return input().split(' ').map(Number); }

function solve(n) {
    const res = new Array(2 * n).fill(0);
    
    // Fill first n positions with n, n-1, ..., 1
    for (let i = 0; i < n; i++) {
        res[i] = n - i;
    }
    
    // Fill remaining positions
    for (let x = n; x >= 1; x--) {
        for (let j = n; j < 2 * n; j += x) {
            if (res[j] === 0) {
                res[j] = x;
                break;
            }
        }
    }
    
    return res;
}

function main() {
    const t = nextInt();
    
    for (let test = 0; test < t; test++) {
        const n = nextInt();
        const res = solve(n);
        
        console.log(res.join(' '));
    }
}

rl.on('line', (line) => { lines.push(line); });
rl.on('close', () => { main(); });