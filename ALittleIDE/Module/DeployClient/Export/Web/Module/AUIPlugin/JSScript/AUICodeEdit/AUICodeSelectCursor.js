{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


AUIPlugin.AUICodeSelectCursor = JavaScript.Class(undefined, {
	Ctor : function(edit) {
		this._clear_quad = true;
		this._edit = edit;
	},
	ClearQuad : function() {
		if (this._clear_quad) {
			return;
		}
		this._clear_quad = true;
		if (this._it_line_start !== undefined && this._it_line_end !== undefined) {
			if (this._it_line_start < this._it_line_end) {
				let line_list = this._edit.line_list;
				let it_line_end = this._it_line_end;
				for (let i = this._it_line_start; i <= it_line_end; i += 1) {
					line_list[i - 1].container._select.visible = false;
				}
			} else {
				let line_list = this._edit.line_list;
				let it_line_start = this._it_line_start;
				for (let i = this._it_line_end; i <= it_line_start; i += 1) {
					line_list[i - 1].container._select.visible = false;
				}
			}
		}
	},
	SetQuad : function() {
		let it_line_start = this._it_line_start;
		let it_char_start = this._it_char_start;
		let it_line_end = this._it_line_end;
		let it_char_end = this._it_char_end;
		let swap = false;
		if (it_line_start > it_line_end) {
			swap = true;
		} else if (it_line_start === it_line_end) {
			swap = it_char_start > it_char_end;
		}
		if (swap) {
			let temp = it_line_start;
			it_line_start = it_line_end;
			it_line_end = temp;
			temp = it_char_start;
			it_char_start = it_char_end;
			it_char_end = temp;
		}
		if (it_line_start === it_line_end) {
			if (this._it_char_start === this._it_char_end) {
				return;
			}
			let line = this._edit.line_list[it_line_start - 1];
			if (line.char_count === 0) {
				return;
			}
			line.container._select.visible = true;
			this._clear_quad = false;
			line.container._select.x = line.char_list[it_char_start + 1 - 1].pre_width;
			line.container._select.width = line.char_list[it_char_end - 1].pre_width + line.char_list[it_char_end - 1].width - line.container._select.x;
			return;
		}
		let line_list = this._edit.line_list;
		for (let i = it_line_start; i <= it_line_end; i += 1) {
			let line = line_list[i - 1];
			if (line.char_count > 0) {
				if (i === it_line_start) {
					if (it_char_start < line.char_count) {
						line.container._select.visible = true;
						this._clear_quad = false;
						line.container._select.x = line.char_list[it_char_start + 1 - 1].pre_width;
						line.container._select.width = line.container.width - line.container._select.x;
					}
				} else if (i === it_line_end) {
					if (it_char_end > 0) {
						line.container._select.visible = true;
						this._clear_quad = false;
						line.container._select.x = 0;
						line.container._select.width = line.char_list[it_char_end - 1].pre_width + line.char_list[it_char_end - 1].width;
					}
				} else {
					line.container._select.visible = true;
					this._clear_quad = false;
					line.container._select.x = 0;
					line.container._select.width = line.container.width;
				}
				if (line.container._select.width <= 0) {
					line.container._select.width = this._edit.ascii_width;
				}
			} else {
				line.container._select.visible = true;
				this._clear_quad = false;
				line.container._select.x = 0;
				line.container._select.width = this._edit.ascii_width;
			}
		}
	},
	get line_start() {
		return this._it_line_start;
	},
	get char_start() {
		return this._it_char_start;
	},
	get line_end() {
		return this._it_line_end;
	},
	get char_end() {
		return this._it_char_end;
	},
	GetLineCharCloseToEnd : function() {
		if (this._it_line_start < this._it_line_end) {
			return [this._it_line_end, this._it_char_end];
		}
		if (this._it_line_start > this._it_line_end) {
			return [this._it_line_start, this._it_char_start];
		}
		if (this._it_char_start < this._it_char_end) {
			return [this._it_line_end, this._it_char_end];
		}
		return [this._it_line_start, this._it_char_start];
	},
	GetLineCharCloseToHome : function() {
		if (this._it_line_start > this._it_line_end) {
			return [this._it_line_end, this._it_char_end];
		}
		if (this._it_line_start < this._it_line_end) {
			return [this._it_line_start, this._it_char_start];
		}
		if (this._it_char_start > this._it_char_end) {
			return [this._it_line_end, this._it_char_end];
		}
		return [this._it_line_start, this._it_char_start];
	},
	StartLineChar : function(line, char) {
		this.Hide();
		if (this._edit.line_count === 0) {
			return;
		}
		this._it_line_start = line;
		this._it_char_start = char;
	},
	UpdateLineChar : function(it_line, it_char) {
		this.ClearQuad();
		this._it_line_end = it_line;
		let line = this._edit.line_list[it_line - 1];
		if (line === undefined) {
			this._it_char_end = 0;
		} else if (line.char_count < it_char) {
			this._it_line_end = line.char_count;
		} else {
			this._it_char_end = it_char;
		}
		this.SetQuad();
	},
	StartOffsetXY : function(x, y) {
		this.Hide();
		if (this._edit.line_count === 0) {
			return;
		}
		[this._it_line_start, this._it_char_start] = this._edit.CalcLineAndChar(x, y);
	},
	UpdateOffsetXY : function(x, y) {
		this.ClearQuad();
		if (this._it_line_start === undefined) {
			return;
		}
		[this._it_line_end, this._it_char_end] = this._edit.CalcLineAndChar(x, y);
		this.SetQuad();
	},
	GetTargetText : function(it_line_start, it_char_start, it_line_end, it_char_end) {
		let swap = false;
		if (it_line_start > it_line_end) {
			swap = true;
		} else if (it_line_start === it_line_end) {
			swap = it_char_start > it_char_end;
		}
		if (swap) {
			let temp = it_line_start;
			it_line_start = it_line_end;
			it_line_end = temp;
			temp = it_char_start;
			it_char_start = it_char_end;
			it_char_end = temp;
		}
		if (it_line_start === it_line_end) {
			if (it_char_start === it_char_end) {
				return "";
			}
			let line = this._edit.line_list[it_line_start - 1];
			if (line.char_count === 0) {
				return "";
			}
			let text = [];
			let text_count = 0;
			for (let i = it_char_start + 1; i <= it_char_end; i += 1) {
				++ text_count;
				text[text_count - 1] = line.char_list[i - 1].char;
			}
			return ALittle.String_Join(text, "");
		}
		let text = [];
		let text_count = 0;
		for (let i = it_line_start; i <= it_line_end; i += 1) {
			let line = this._edit.line_list[i - 1];
			if (line.char_count > 0) {
				if (i === it_line_start) {
					for (let j = it_char_start + 1; j <= line.char_count; j += 1) {
						++ text_count;
						text[text_count - 1] = line.char_list[j - 1].char;
					}
				} else if (i === it_line_end) {
					for (let j = 1; j <= it_char_end; j += 1) {
						++ text_count;
						text[text_count - 1] = line.char_list[j - 1].char;
					}
				} else {
					for (let j = 1; j <= line.char_count; j += 1) {
						++ text_count;
						text[text_count - 1] = line.char_list[j - 1].char;
					}
				}
			}
		}
		return ALittle.String_Join(text, "");
	},
	GetSelectText : function() {
		if (this._it_line_start === undefined) {
			return undefined;
		}
		return this.GetTargetText(this._it_line_start, this._it_char_start, this._it_line_end, this._it_char_end);
	},
	DeleteSelect : function(need_revoke, revoke_bind) {
		if (this._it_line_start === undefined) {
			return [false, undefined, undefined];
		}
		let edit_line_list = this._edit.line_list;
		if (this._it_line_start === this._it_line_end) {
			if (this._it_char_start === this._it_char_end) {
				this.Hide();
				return [false, undefined, undefined];
			}
			let line = edit_line_list[this._it_line_start - 1];
			if (line === undefined) {
				return [false, undefined, undefined];
			}
			let old_it_line_start = this._it_line_start;
			let old_it_char_start = this._it_char_start;
			let old_it_line_end = this._it_line_end;
			let old_it_char_end = this._it_char_end;
			let it_line_start = this._it_line_start;
			let it_char_start = this._it_char_start;
			let it_char_end = this._it_char_end;
			if (it_char_start > it_char_end) {
				let temp = it_char_start;
				it_char_start = it_char_end;
				it_char_end = temp;
			}
			if (this._edit.language !== undefined) {
				this._edit.language.DeleteText(it_line_start, it_char_start, it_line_start, it_char_end - 1);
			}
			this.Hide();
			let acc_width = 0.0;
			for (let i = it_char_start + 1; i <= it_char_end; i += 1) {
				acc_width = acc_width + (line.char_list[i - 1].width);
			}
			for (let i = it_char_end + 1; i <= line.char_count; i += 1) {
				let char = line.char_list[i - 1];
				char.pre_width = char.pre_width - (acc_width);
				if (char.text !== undefined) {
					char.text.x = char.text.x - (acc_width);
				}
			}
			let revoke_content = "";
			for (let i = it_char_start + 1; i <= it_char_end; i += 1) {
				let char = line.char_list[i - 1];
				revoke_content = revoke_content + char.char;
				if (char.text !== undefined) {
					line.container._text.RemoveChild(char.text);
				}
			}
			let count = it_char_end - it_char_start;
			line.char_count = line.char_count - (count);
			ALittle.List_Splice(line.char_list, it_char_start + 1, count);
			let last_char = line.char_list[line.char_count - 1];
			if (last_char !== undefined) {
				line.container.width = last_char.pre_width + last_char.width;
			} else {
				line.container.width = 0;
			}
			let rejust = true;
			let ___OBJECT_1 = edit_line_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let line_info = ___OBJECT_1[index - 1];
				if (line_info === undefined) break;
				if (line_info.container.width > line.container.width) {
					rejust = false;
					break;
				}
			}
			if (rejust) {
				this._edit.AdjustCodeScreen(line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH);
			}
			if (need_revoke) {
				let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteSelectRevoke, this._edit, this._edit.cursor, this, old_it_line_start, old_it_char_start, old_it_line_end, old_it_char_end, it_line_start, it_char_start, revoke_content, revoke_bind === undefined);
				if (revoke_bind !== undefined) {
					revoke_bind.PushRevoke(revoke);
				} else {
					this._edit.revoke_list.PushRevoke(revoke);
				}
			}
			this._edit.UpdateLineFind(it_line_start);
			return [true, it_line_start, it_char_start];
		}
		let old_it_line_start = this._it_line_start;
		let old_it_char_start = this._it_line_start;
		let old_it_line_end = this._it_line_end;
		let old_it_char_end = this._it_char_end;
		let it_line_start = this._it_line_start;
		let it_char_start = this._it_char_start;
		let it_line_end = this._it_line_end;
		let it_char_end = this._it_char_end;
		if (it_line_start > it_line_end) {
			let temp = it_line_start;
			it_line_start = it_line_end;
			it_line_end = temp;
			temp = it_char_start;
			it_char_start = it_char_end;
			it_char_end = temp;
		}
		if (this._edit.language !== undefined) {
			let delete_line_end = it_line_end;
			let delete_char_end = it_char_end - 1;
			if (delete_char_end < 0) {
				delete_line_end = delete_line_end - (1);
				delete_char_end = edit_line_list[delete_line_end - 1].char_count - 1;
			}
			this._edit.language.DeleteText(it_line_start, it_char_start, delete_line_end, delete_char_end);
		}
		this.Hide();
		let revoke_center = [];
		let revoke_c_count = 0;
		let line_count = it_line_end - it_line_start - 1;
		if (line_count > 0) {
			for (let it_line = it_line_start + 1; it_line < it_line_end; it_line += 1) {
				let line = edit_line_list[it_line - 1];
				for (let it_char = 1; it_char <= line.char_count; it_char += 1) {
					revoke_c_count = revoke_c_count + (1);
					revoke_center[revoke_c_count - 1] = line.char_list[it_char - 1].char;
				}
			}
			this._edit.code_linear.SpliceChild(it_line_start + 1, line_count);
			ALittle.List_Splice(edit_line_list, it_line_start + 1, line_count);
			this._edit.line_count = this._edit.line_count - (line_count);
			it_line_end = it_line_end - (line_count);
		}
		let revoke_start = "";
		let start_line = edit_line_list[it_line_start - 1];
		for (let it_char = it_char_start + 1; it_char <= start_line.char_count; it_char += 1) {
			let char = start_line.char_list[it_char - 1];
			revoke_start = revoke_start + char.char;
			if (char.text !== undefined) {
				start_line.container._text.RemoveChild(char.text);
			}
		}
		let count = start_line.char_count - it_char_start;
		start_line.char_count = start_line.char_count - (count);
		ALittle.List_Splice(start_line.char_list, it_char_start + 1, count);
		let end_line = edit_line_list[it_line_end - 1];
		let pre_width = 0.0;
		let last_char = start_line.char_list[start_line.char_count - 1];
		if (last_char !== undefined) {
			pre_width = last_char.pre_width + last_char.width;
		}
		let revoke_end = "";
		for (let i = 1; i <= it_char_end; i += 1) {
			revoke_end = revoke_end + end_line.char_list[i - 1].char;
		}
		for (let i = it_char_end + 1; i <= end_line.char_count; i += 1) {
			let char = end_line.char_list[i - 1];
			char.pre_width = pre_width;
			if (char.text !== undefined) {
				char.text.x = pre_width;
			}
			start_line.container.AddChar(char);
			pre_width = pre_width + (char.width);
			start_line.char_count = start_line.char_count + (1);
			start_line.char_list[start_line.char_count - 1] = char;
		}
		start_line.container.width = pre_width;
		this._edit.code_linear.RemoveChild(end_line.container);
		this._edit.line_count = this._edit.line_count - (1);
		ALittle.List_Remove(edit_line_list, it_line_end);
		let max_width = 0.0;
		let ___OBJECT_2 = edit_line_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let line = ___OBJECT_2[index - 1];
			if (line === undefined) break;
			if (max_width < line.container.width) {
				max_width = line.container.width;
			}
		}
		this._edit.AdjustCodeScreen(max_width);
		if (need_revoke) {
			let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteSelectRevoke, this._edit, this._edit.cursor, this, old_it_line_start, old_it_char_start, old_it_line_end, old_it_char_end, it_line_start, it_char_start, revoke_start + ALittle.String_Join(revoke_center, "") + revoke_end, revoke_bind === undefined);
			if (revoke_bind !== undefined) {
				revoke_bind.PushRevoke(revoke);
			} else {
				this._edit.revoke_list.PushRevoke(revoke);
			}
		}
		for (let i = it_line_start; i <= it_line_end; i += 1) {
			this._edit.UpdateLineFind(i);
		}
		this._edit.UpdateLineNumber();
		return [true, it_line_start, it_char_start];
	},
	TryHide : function() {
		if (this._it_line_start === undefined || this._it_line_end === undefined || this._it_char_start === undefined || this._it_char_end === undefined) {
			this.Hide();
			return;
		}
		if (this._it_line_start === this._it_line_end && this._it_char_start === this._it_char_end) {
			this.Hide();
			return;
		}
	},
	Hide : function() {
		this.ClearQuad();
		this._clear_quad = true;
		this._it_line_start = undefined;
		this._it_char_start = undefined;
		this._it_line_end = undefined;
		this._it_char_end = undefined;
	},
}, "AUIPlugin.AUICodeSelectCursor");

}