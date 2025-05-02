//config
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const seed = 4208;
const n3 = 0;
const n4 = 8;
const n = 10;
const k1 = 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3;
const w = canvas.width;
const h = canvas.height;

//matrix
function genRandNum(seed) {
    const RANDOM_NUMBER = 2147483647;
    let value = seed % RANDOM_NUMBER;
    if (value <= 0) value += RANDOM_NUMBER;

    return function () {
        value = (value * 16807) % RANDOM_NUMBER;
        return (value - 1) / RANDOM_NUMBER;
    };
}

function genDirMatrix(rand, k) {
    const rawMatrix = Array.from({length: n}, () =>
        Array.from({length: n}, () => rand() * 2.0)
    );

    const dirMatrix = rawMatrix.map((row) =>
        row.map((value) => (value * k >= 1.0 ? 1 : 0))
    );

    return dirMatrix;
}

function genUndirMatrix(dir) {
    const undir = Array.from({length: n}, () => Array(n).fill(0));

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (dir[i][j] === 1 || dir[j][i] === 1) {
                undir[i][j] = 1;
                undir[j][i] = 1;
            }
        }
    }

    return undir;
}

function printMatrix(matrix, title) {
    console.log(`\n ${title} `);
    matrix.forEach((row) => {
        const line = row.map((v) => (v === 1 ? '1 ' : '0 ')).join(' ');
        console.log(line);
    });
}

//drawing
const PADD = 50;

const positions = [
    {x: PADD, y: PADD},
    {x: w / 2, y: PADD},
    {x: w - PADD, y: PADD},
    {x: w - PADD, y: h / 2},
    {x: w - PADD, y: h - PADD},
    {x: (w / 3) * 2, y: h - PADD},
    {x: w / 3, y: h - PADD},
    {x: PADD, y: h - PADD},
    {x: PADD, y: h / 2},
    {x: w / 2, y: h / 2},
];

function distanceToLine(p1, p2, p) {
    const A = p.x - p1.x;
    const B = p.y - p1.y;
    const C = p2.x - p1.x;
    const D = p2.y - p1.y;

    const scal = A * C + B * D;
    const len2 = C * C + D * D;
    const param = scal / len2;

    let xx;
    let yy;

    if (param < 0) {
        xx = p1.x;
        yy = p1.y;
    } else if (param > 1) {
        xx = p2.x;
        yy = p2.y;
    } else {
        xx = p1.x + param * C;
        yy = p1.y + param * D;
    }

    const vx = p.x - xx;
    const vy = p.y - yy;
    return Math.sqrt(vx * vx + vy * vy);
}

function drawArrow(from, to, rad, controlPoint) {
    let angle;

    if (controlPoint) {
        const t = 0.95;
        const x = 2 * (1 - t) * (controlPoint.x - from.x) + 2 * t * (to.x - controlPoint.x);
        const y = 2 * (1 - t) * (controlPoint.y - from.y) + 2 * t * (to.y - controlPoint.y);
        angle = Math.atan2(y, x);
    } else {
        angle = Math.atan2(to.y - from.y, to.x - from.x);
    }

    const x = to.x - rad * Math.cos(angle);
    const y = to.y - rad * Math.sin(angle);

    ctx.beginPath();
    ctx.moveTo(x, y);
    ctx.lineTo(
        x - 10 * Math.cos(angle - Math.PI / 10),
        y - 10 * Math.sin(angle - Math.PI / 10)
    );
    ctx.lineTo(
        x - 10 * Math.cos(angle + Math.PI / 10),
        y - 10 * Math.sin(angle + Math.PI / 10)
    );
    ctx.fill();
    ctx.closePath();
}

function getCurvPoint(p1, p2, i, j, OFFSET, direction) {
    const midX = (p1.x + p2.x) / 2;
    const midY = (p1.y + p2.y) / 2;

    const vx = p2.x - p1.x;
    const vy = p2.y - p1.y;

    const perp = {x: -vy, y: vx};

    const length = Math.sqrt(perp.x * perp.x + perp.y * perp.y);

    const dir = direction ? direction : (i < j ? 1 : -1);

    const point = {
        x: midX + dir * (perp.x / length) * OFFSET,
        y: midY + dir * (perp.y / length) * OFFSET,
    };

    return point;
}

function drawGraph(matrix, directed = true) {
    ctx.clearRect(0, 0, w, h);

    const RAD = 20;

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (matrix[i][j] === 1) {
                if (directed && matrix[j][i] === 1 && j < i) continue;
                if (!directed && j < i) continue;
                if (i === j) {
                    let offsetX;
                    let offsetY;
                    const x = positions[i].x;
                    const y = positions[i].y;

                    if (y === PADD) {
                        offsetX = 0;
                        offsetY = -20;
                    } else if (y === h / 2 && x === w - PADD) {
                        offsetX = 20;
                        offsetY = 0;
                    } else if (y === h / 2 || (x === w / 2 && y === h / 2)) {
                        offsetX = -20;
                        offsetY = 0;
                    } else if (y === h - PADD) {
                        offsetX = 0;
                        offsetY = 20;
                    }
                    const cx = positions[i].x + offsetX;
                    const cy = positions[i].y + offsetY;

                    ctx.beginPath();
                    ctx.arc(cx, cy, RAD, Math.PI, -Math.PI);
                    ctx.stroke();

                    continue;
                }
                const p1 = positions[i];
                const p2 = positions[j];

                let curved = false;
                let curvPoint = null;

                for (let k = 0; k < n; k++) {
                    if (j === i) break;
                    if (k === i || k === j) continue;
                    const pk = positions[k];

                    if (distanceToLine(p1, p2, pk) < 25) {
                        curved = true;

                        curvPoint = getCurvPoint(p1, p2, i, j, 90)
                    }
                }

                ctx.beginPath();
                ctx.moveTo(p1.x, p1.y);

                if (curved) {
                    ctx.quadraticCurveTo(curvPoint.x, curvPoint.y, p2.x, p2.y);
                } else {
                    ctx.lineTo(p2.x, p2.y);
                }
                ctx.stroke();

                if (directed) {
                    drawArrow(p1, p2, RAD, curved ? curvPoint : null);

                    if (matrix[j][i] === 1) {
                        const curvPoint2 = getCurvPoint(p1, p2, i, j, 90, -1)

                        ctx.beginPath();
                        ctx.moveTo(p1.x, p1.y);

                        ctx.quadraticCurveTo(curvPoint2.x, curvPoint2.y, p2.x, p2.y);
                        ctx.stroke();

                        drawArrow(p2, p1, RAD, curvPoint2);
                    }
                }
            }
        }
    }

    for (let i = 0; i < n; i++) {
        ctx.beginPath();
        ctx.arc(positions[i].x, positions[i].y, RAD, Math.PI, -Math.PI);
        ctx.fillStyle = 'white';
        ctx.fill();
        ctx.stroke();
        ctx.fillStyle = 'black';
        ctx.font = '15px Arial';
        ctx.fillText(i + 1, positions[i].x - 5, positions[i].y + 5);
    }
}

//button's functions
const rand = genRandNum(seed);
const dirMatrix = genDirMatrix(rand, k1);
const undirMatrix = genUndirMatrix(dirMatrix);

printMatrix(dirMatrix, 'Directed Matrix');
printMatrix(undirMatrix, 'Undirected Matrix');

function drawDirected1() {
    drawGraph(dirMatrix, true);
}

function drawUndirected1() {
    drawGraph(undirMatrix, false);
}