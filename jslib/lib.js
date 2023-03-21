mergeInto(LibraryManager.library, {
  _draw_entity_to_canvas: function(id, color, mv) {
    gl.uniform4fv(colorLoc, new Float32Array([1.0, 1.0, 1.0, 1.0]));
    gl.uniformMatrix4fv(mvLoc, false, new Float32Array(identity4x4));
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, defaultTexture);
    gl.uniform1i(textureLoc, 0);
    gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);
  },

  _clear_canvas: function() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  },

  _setup_sprite_draw: function() {
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.vertexAttribPointer(posLoc, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(posLoc);

    gl.bindBuffer(gl.ARRAY_BUFFER, texCoordsBuffer);
    gl.vertexAttribPointer(texCoordLoc, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(texCoordLoc);

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

    gl.uniformMatrix4fv(projLoc, false, new Float32Array(identity4x4));
  },
});
