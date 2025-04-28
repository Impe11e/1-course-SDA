// === CONFIG ===
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const seed = 4111;
const n3 = 1;
const n4 = 1;
const n = 10 + n3;
const k = 1.0 - n3 * 0.02 - n4 * 0.005 - 0.25; // = 0.725
const w = canvas.width;
const h = canvas.height;
const RAD = 20;

// === RANDOM ===
function genRand(seed) {
  const MOD = 2147483647;
  let val = seed % MOD;
  return function () {
    val = (val * 16807) % MOD;
    return (val - 1) / MOD;
  };
}

// === MATRIX ===
function genDirMatrix(rand, k) {
  const raw = Array.from({ length: n }, () =>
      Array.from({ length: n }, () => rand() * 2)
  );

  let dir = raw.map((row) =>
      row.map((v) => (v * k >= 1 ? 1 : 0))
  );

  // прибираємо двосторонні стрілки
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      if (dir[i][j] && dir[j][i]) {
        if (Math.random() < 0.5) dir[i][j] = 0;
        else dir[j][i] = 0;
      }
    }
  }

  return dir;
}

function genUndirMatrix(dir) {
  const undir = Array.from({ length: n }, () => Array(n).fill(0));
  for (let i = 0; i < n; i++)
    for (let j = 0; j < n; j++)
      if (dir[i][j] || dir[j][i])
        undir[i][j] = undir[j][i] = 1;
  return undir;
}

function printMatrix(matrix, title) {
  console.log(`\n${title}:`);
  matrix.forEach((row) => console.log(row.join(" ")));
}

// === POSITIONS (circle) ===
const centerX = w / 2;
const centerY = h / 2;
const radius = 280;

const positions = Array.from({ length: n }, (_, i) => {
  const angle = (2 * Math.PI * i) / n - Math.PI / 2;
  return {
    x: centerX + radius * Math.cos(angle),
    y: centerY + radius * Math.sin(angle),
  };
});

// === DRAWING ===
function drawArrow(from, to, point = null) {
  let dx, dy;
  if (point) {
    dx = to.x - point.x;
    dy = to.y - point.y;
  } else {
    dx = to.x - from.x;
    dy = to.y - from.y;
  }

  const angle = Math.atan2(dy, dx);
  const x = to.x - RAD * Math.cos(angle);
  const y = to.y - RAD * Math.sin(angle);

  ctx.beginPath();
  ctx.moveTo(x, y);
  ctx.lineTo(
      x - 10 * Math.cos(angle - Math.PI / 8),
      y - 10 * Math.sin(angle - Math.PI / 8)
  );
  ctx.lineTo(
      x - 10 * Math.cos(angle + Math.PI / 8),
      y - 10 * Math.sin(angle + Math.PI / 8)
  );
  ctx.closePath();
  ctx.fill();
}

function drawGraph(matrix, directed = true) {
  ctx.clearRect(0, 0, w, h);
  ctx.strokeStyle = "#333";
  ctx.fillStyle = "#000";

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      if (!matrix[i][j]) continue;
      if (!directed && j < i) continue;

      if (i === j) {
        const loopOffset = 30;
        ctx.beginPath();
        ctx.arc(positions[i].x, positions[i].y - loopOffset, RAD, 0, Math.PI * 2);
        ctx.stroke();
        continue;
      }

      const p1 = positions[i];
      const p2 = positions[j];

      // curved edges if overlap
      let curved = false;
      let cp = null;

      for (let k = 0; k < n; k++) {
        if (k === i || k === j) continue;
        const pk = positions[k];
        const d = distanceToLine(p1, p2, pk);
        if (d < 25) {
          curved = true;
          const mid = { x: (p1.x + p2.x) / 2, y: (p1.y + p2.y) / 2 };
          const vx = p2.x - p1.x, vy = p2.y - p1.y;
          const perp = { x: -vy, y: vx };
          const len = Math.sqrt(perp.x ** 2 + perp.y ** 2);
          const OFFSET = 90;
          const dir = i < j ? 1 : -1;
          cp = {
            x: mid.x + dir * (perp.x / len) * OFFSET,
            y: mid.y + dir * (perp.y / len) * OFFSET
          };
          break;
        }
      }

      ctx.beginPath();
      ctx.moveTo(p1.x, p1.y);
      if (curved) {
        ctx.quadraticCurveTo(cp.x, cp.y, p2.x, p2.y);
      } else {
        ctx.lineTo(p2.x, p2.y);
      }
      ctx.stroke();

      if (directed) {
        drawArrow(p1, p2, curved ? cp : null);
      }
    }
  }

  // draw vertices
  for (let i = 0; i < n; i++) {
    ctx.beginPath();
    ctx.fillStyle = "#fff";
    ctx.arc(positions[i].x, positions[i].y, RAD, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
    ctx.fillStyle = "#000";
    ctx.font = "15px Arial";
    ctx.textAlign = "center";
    ctx.textBaseline = "middle";
    ctx.fillText(i + 1, positions[i].x, positions[i].y);
  }
}

function distanceToLine(p1, p2, p) {
  const A = p.x - p1.x;
  const B = p.y - p1.y;
  const C = p2.x - p1.x;
  const D = p2.y - p1.y;
  const dot = A * C + B * D;
  const len2 = C * C + D * D;
  const param = dot / len2;
  let xx, yy;
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
  const dx = p.x - xx;
  const dy = p.y - yy;
  return Math.sqrt(dx * dx + dy * dy);
}

// === INIT + BUTTONS ===
const rand = genRand(seed);
const dirMatrix = genDirMatrix(rand, k);
const undirMatrix = genUndirMatrix(dirMatrix);

printMatrix(dirMatrix, "Directed Matrix");
printMatrix(undirMatrix, "Undirected Matrix");

function drawDirected() {
  drawGraph(dirMatrix, true);
}
function drawUndirected() {
  drawGraph(undirMatrix, false);
}

