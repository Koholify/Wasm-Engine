mergeInto(LibraryManager.library, {
  _draw_entity_to_canvas: function(id, color, mv) {
    const bytes_per = 4;
    const c = HEAPF32.subarray(color/bytes_per, color/bytes_per + 4);
    const m = HEAPF32.subarray(mv/bytes_per, mv/bytes_per + 16);
    gl.uniform4fv(colorLoc, c);
    gl.uniformMatrix4fv(mvLoc, false, m); 
    gl.activeTexture(gl.TEXTURE0);
    const t_id = id > 0 ? id : 1;
    gl.bindTexture(gl.TEXTURE_2D, TextureMap[t_id]);
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
  
  _get_texture_from_name: function(name) {
    return StoredTextures[UTF8ToString(name)];
  },
});
