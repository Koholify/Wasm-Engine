const vertexBasic = `\
#version 300 es

in vec4 position;
in vec2 texCoords;

uniform mat4 projectionMatix;
uniform mat4 modelViewMatrix;

out vec2 oTexCoords;

void main() {
  gl_Position = projectionMatix * modelViewMatrix * position;
  oTexCoords = texCoords;
}
`

const fragmentBasic = `\
#version 300 es
precision mediump float;

in vec2 oTexCoords;

out vec4 fragColor;
uniform sampler2D texture0;
uniform vec4 fcolor;

void main() {
  fragColor = fcolor * texture(texture0, oTexCoords);
}
`

const compileShader = function(shaderType, source) {
  let shader = gl.createShader(shaderType);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);

  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    const info = gl.getShaderInfoLog(shader);
    console.error(`Failed to comile shader. \n\n${info}`);
  }

  return shader;
}

const compileProgram = function() {
  const vertex = compileShader(gl.VERTEX_SHADER, vertexBasic);
  const fragment = compileShader(gl.FRAGMENT_SHADER, fragmentBasic);

  let program = gl.createProgram();
  gl.attachShader(program, vertex);
  gl.attachShader(program, fragment);
  gl.linkProgram(program);

  if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
    const info = gl.getProgramInfoLog(program);
    console.log(`Could not compile WebGL Program. \n\n${info}`);
  }

  gl.detachShader(program, vertex);
  gl.detachShader(program, fragment);
  gl.deleteShader(vertex);
  gl.deleteShader(fragment);
  return program;
}

const _draw_entity_to_canvas = function(id, color, mv) {
  gl.uniform4fv(colorLoc, new Float32Array([1.0, 1.0, 1.0, 1.0]));
  gl.uniformMatrix4fv(mvLoc, false, new Float32Array(identity4x4));
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, defaultTexture);
  gl.uniform1i(textureLoc, 0);
  gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);
}

const _clear_canvas = function() {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
}

const _setup_sprite_draw = function() {
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.vertexAttribPointer(posLoc, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(posLoc);

  gl.bindBuffer(gl.ARRAY_BUFFER, texCoordsBuffer);
  gl.vertexAttribPointer(texCoordLoc, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(texCoordLoc);

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

  gl.uniformMatrix4fv(projLoc, false, new Float32Array(identity4x4));
}

const canvas = document.getElementById('gl-canvas');
const gl = canvas.getContext('webgl2');

gl.viewport(0, 0, canvas.width, canvas.height);
gl.clearColor(0, 0, 0, 1);
gl.enable(gl.DEPTH_TEST);
gl.enable(gl.BLEND);
gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

const program = compileProgram();
gl.useProgram(program);

const mvLoc = gl.getUniformLocation(program, 'modelViewMatrix');
const projLoc = gl.getUniformLocation(program, 'projectionMatix');
const colorLoc = gl.getUniformLocation(program, 'fcolor');
const textureLoc = gl.getUniformLocation(program, 'texture0');

const posLoc = gl.getAttribLocation(program, 'position')
const texCoordLoc = gl.getAttribLocation(program, 'texCoords');

const identity4x4 = [
  1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0
];

const vertexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
const positions = [
   0.5,  0.5,
  -0.5,  0.5,
   0.5, -0.5,
  -0.5, -0.5,
];

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

const texCoordsBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, texCoordsBuffer);
const coords = [
  1.0, 1.0,
  0.0, 1.0,
  1.0, 0.0,
  0.0, 0.0,
];

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(coords), gl.STATIC_DRAW);

const indexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
const indicies = [
  0, 1, 2, 1, 3, 2
];
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Int16Array(indicies), gl.STATIC_DRAW);

const StoredTextures = {};
const TextureMap = {};
let TEXTURE_COUNT = 0;

const defaultTexture = gl.createTexture();
gl.bindTexture(gl.TEXTURE_2D, defaultTexture);
gl.texImage2D(
  gl.TEXTURE_2D, // type
  0, // level
  gl.RGBA, // internal format
  1, // width
  1, // height
  0, // border
  gl.RGBA, // src format
  gl.UNSIGNED_BYTE, // src type
  new Uint8Array([255, 255, 255, 255]));

StoredTextures['default'] = ++TEXTURE_COUNT;
TextureMap[TEXTURE_COUNT] = defaultTexture;

