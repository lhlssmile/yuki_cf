const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

let lines = [];
let currentLine = 0;

function input() { return lines[currentLine++]; }
function nextInt() { return parseInt(input()); }
function nextIntArray() { return input().split(' ').map(Number); }

const INF = 0x3f3f3f3f;
const MOD = 1000000007;

function solve() {
    const t = nextInt();
    
    for (let test = 0; test < t; test++) {
        const n = nextInt();
        const a = nextIntArray();
        
        const odds = [];
        const evens = [];
        let sumE = 0;
        
        for (let x of a) {
            if (x % 2 === 0) {
                evens.push(x);
                sumE += x;
            } else {
                odds.push(x);
            }
        }
        
        const k = odds.length;
        if (k === 0) {
            console.log(0);
            continue;
        }
        
        odds.sort((a, b) => a - b);
        
        let sumO = 0;
        for (let x of odds) {
            sumO += x;
        }
        
        const sac = Math.floor(k / 2);
        let sumSac = 0;
        for (let i = 0; i < sac; i++) {
            sumSac += odds[i];
        }
        
        const ans = sumO - sumSac + sumE;
        console.log(ans);
    }
}

rl.on('line', (line) => { lines.push(line); });
rl.on('close', () => { solve(); });