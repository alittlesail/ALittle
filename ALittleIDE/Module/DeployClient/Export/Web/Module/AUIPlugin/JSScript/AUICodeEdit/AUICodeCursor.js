{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


if (ALittle.Quad === undefined) throw new Error(" extends class:ALittle.Quad is undefined");
AUIPlugin.AUICodeCursor = JavaScript.Class(ALittle.Quad, {
	Ctor : function(ctrl_sys, edit) {
		this._flash_alpha = 0;
		this._flash_dir = 0.05;
		this._it_line = 1;
		this._it_char = 0;
		this._virtual_indent = 0;
		this._move_acc_width = 0;
		this._edit = edit;
	},
	get line() {
		return this._it_line;
	},
	get char() {
		return this._it_char;
	},
	get virtual_indent() {
		if (this._virtual_indent === 0) {
			return "";
		}
		let indent = this._virtual_indent;
		let indent_str = "";
		for (let i = 1; i <= indent; i += 1) {
			indent_str = indent_str + " ";
		}
		return indent_str;
	},
	Show : function(x, y) {
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		if (!A_LoopSystem.HasUpdater(this._loop)) {
			A_LoopSystem.AddUpdater(this._loop);
		}
		this.visible = true;
	},
	GetCurCharInLine : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return undefined;
		}
		let index = this._it_char + 1;
		if (index > line.char_count) {
			return undefined;
		}
		return line.char_list[index - 1].char;
	},
	GetNextCharInLine : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return undefined;
		}
		let index = this._it_char + 2;
		if (index > line.char_count) {
			return undefined;
		}
		return line.char_list[index - 1].char;
	},
	CalcSelectWord : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return [undefined, undefined];
		}
		let count = line.char_count;
		while (count > 0 && line.char_list[count - 1].width <= 0) {
			-- count;
		}
		let cur_char = line.char_list[this._it_char + 1 - 1];
		let is_word = ALittle.String_IsWordChar(cur_char.char);
		let it_end = this._it_char;
		for (let i = this._it_char + 1; i <= count; i += 1) {
			if (ALittle.String_IsWordChar(line.char_list[i - 1].char) !== is_word) {
				break;
			}
			it_end = i;
		}
		let it_start = this._it_char;
		for (let i = this._it_char; i >= 1; i += -1) {
			if (ALittle.String_IsWordChar(line.char_list[i - 1].char) !== is_word) {
				break;
			}
			it_start = i - 1;
		}
		if (it_start === it_end) {
			return [undefined, undefined];
		}
		return [it_start, it_end];
	},
	SetOffsetXY : function(x, y, show) {
		if (this._edit.line_count <= 0) {
			this._it_line = 1;
			this._it_char = 0;
		} else {
			[this._it_line, this._it_char] = this._edit.CalcLineAndChar(x, y);
		}
		this.y = (this._it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined || this._it_char === 0) {
			this.x = 0;
		} else {
			let char = line.char_list[this._it_char - 1];
			this.x = char.pre_width + char.width;
		}
		if (show === undefined || show) {
			this.Show();
		}
		this._virtual_indent = 0;
		this._move_acc_width = this.x;
	},
	SetLineChar : function(it_line, it_char) {
		this.SetLineCharInner(it_line, it_char);
		this._move_acc_width = this.x;
	},
	SetLineCharInner : function(it_line, it_char) {
		this._it_line = it_line;
		this._it_char = it_char;
		this.y = (this._it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT;
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined || this._it_char <= 0) {
			this.x = 0;
		} else {
			this.x = line.char_list[this._it_char - 1].pre_width + line.char_list[this._it_char - 1].width;
		}
		this._virtual_indent = 0;
	},
	CurLineHasChar : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return false;
		}
		if (line.char_count < 1 || line.char_list[1 - 1].char === "\r" || line.char_list[1 - 1].char === "\n") {
			return false;
		}
		return true;
	},
	AdjustShowCursor : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return;
		}
		if (line.char_count < 1 || line.char_list[1 - 1].char === "\r" || line.char_list[1 - 1].char === "\n") {
			if (this._edit.language !== undefined) {
				this._virtual_indent = this._edit.language.QueryDesiredIndent(this._it_line, this._it_char);
				if (this._virtual_indent > 0) {
					this.x = this._virtual_indent * this._edit.ascii_width;
					if (this.x > this._move_acc_width) {
						this._move_acc_width = this.x;
					}
				}
			}
		}
	},
	UpdateVirtualIndent : function() {
		if (this._edit.language !== undefined) {
			this._virtual_indent = this._edit.language.QueryDesiredIndent(this._it_line, this._it_char);
		}
	},
	OffsetUp : function() {
		if (this._it_line <= 1) {
			return;
		}
		let it_line = this._it_line - 1;
		let line = this._edit.line_list[it_line - 1];
		if (line === undefined) {
			return;
		}
		let it_char = line.char_count;
		while (it_char > 0 && line.char_list[it_char - 1].width <= 0) {
			-- it_char;
		}
		while (it_char > 0) {
			if (line.char_list[it_char - 1].pre_width + line.char_list[it_char - 1].width <= this._move_acc_width) {
				break;
			}
			-- it_char;
		}
		this.SetLineCharInner(it_line, it_char);
	},
	OffsetDown : function() {
		if (this._it_line >= this._edit.line_count) {
			return;
		}
		let it_line = this._it_line + 1;
		let line = this._edit.line_list[it_line - 1];
		if (line === undefined) {
			return;
		}
		let it_char = line.char_count;
		while (it_char > 0 && line.char_list[it_char - 1].width <= 0) {
			-- it_char;
		}
		while (it_char > 0) {
			if (line.char_list[it_char - 1].pre_width + line.char_list[it_char - 1].width <= this._move_acc_width) {
				break;
			}
			-- it_char;
		}
		this.SetLineCharInner(it_line, it_char);
	},
	OffsetLeft : function(ctrl) {
		if (this._it_char > 0) {
			if (!ctrl) {
				this.SetLineChar(this._it_line, this._it_char - 1);
				return;
			}
			let line = this._edit.line_list[this._it_line - 1];
			if (line === undefined) {
				return;
			}
			let cur_char = line.char_list[this._it_char - 1];
			let is_word = ALittle.String_IsWordChar(cur_char.char);
			let it_char = this._it_char - 1;
			while (it_char > 0) {
				if (ALittle.String_IsWordChar(line.char_list[it_char - 1].char) !== is_word) {
					this.SetLineChar(this._it_line, it_char);
					return;
				}
				-- it_char;
			}
			this.SetLineChar(this._it_line, 0);
			return;
		}
		if (this._it_line > 1) {
			let it_line = this._it_line - 1;
			let line = this._edit.line_list[it_line - 1];
			let it_char = line.char_count;
			while (it_char > 0 && line.char_list[it_char - 1].width <= 0) {
				-- it_char;
			}
			this.SetLineChar(it_line, it_char);
			return;
		}
		this.SetLineChar(1, 0);
	},
	OffsetRight : function(ctrl) {
		if (this._edit.line_count <= 0) {
			return;
		}
		let line = this._edit.line_list[this._it_line - 1];
		let count = line.char_count;
		while (count > 0 && line.char_list[count - 1].width <= 0) {
			-- count;
		}
		if (this._it_char < count) {
			if (!ctrl) {
				this.SetLineChar(this._it_line, this._it_char + 1);
				return;
			}
			let cur_char = line.char_list[this._it_char + 1 - 1];
			let is_word = ALittle.String_IsWordChar(cur_char.char);
			let it_char = this._it_char + 1;
			while (it_char <= count) {
				if (ALittle.String_IsWordChar(line.char_list[it_char + 1 - 1].char) !== is_word) {
					this.SetLineChar(this._it_line, it_char);
					return;
				}
				++ it_char;
			}
			this.SetLineChar(this._it_line, count);
			return;
		}
		if (this._it_line >= this._edit.line_count) {
			return;
		}
		this.SetLineChar(this._it_line + 1, 0);
	},
	OffsetHome : function() {
		if (this._it_char <= 0) {
			return;
		}
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return;
		}
		let it_char = 1;
		while (it_char <= line.char_count) {
			let char = line.char_list[it_char - 1];
			if (char.char !== " " && char.char !== "\t") {
				break;
			}
			++ it_char;
		}
		if (this._it_char === it_char - 1) {
			this.SetLineChar(this._it_line, 0);
		} else {
			this.SetLineChar(this._it_line, it_char - 1);
		}
	},
	OffsetEnd : function() {
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return;
		}
		let count = line.char_count;
		while (count > 0 && line.char_list[count - 1].width <= 0) {
			-- count;
		}
		if (this._it_char < count) {
			this.SetLineChar(this._it_line, count);
		}
	},
	DeleteLeft : function(need_revoke, revoke_bind) {
		let old_it_line = this._it_line;
		let old_it_char = this._it_char;
		if (this._it_char > 0) {
			let line = this._edit.line_list[this._it_line - 1];
			if (line === undefined) {
				return false;
			}
			let char = line.char_list[this._it_char - 1];
			let revoke_content = char.char;
			if (char.text !== undefined) {
				line.container._text.RemoveChild(char.text);
			}
			line.char_count = line.char_count - (1);
			ALittle.List_Remove(line.char_list, this._it_char);
			for (let i = this._it_char; i <= line.char_count; i += 1) {
				line.char_list[i - 1].pre_width = line.char_list[i - 1].pre_width - (char.width);
				if (line.char_list[i - 1].text !== undefined) {
					line.char_list[i - 1].text.x = line.char_list[i - 1].text.x - (char.width);
				}
			}
			this.SetLineChar(this._it_line, this._it_char - 1);
			if (this._edit.language !== undefined) {
				this._edit.language.DeleteText(this._it_line, this._it_char, this._it_line, this._it_char);
			}
			let last_char = line.char_list[line.char_count - 1];
			if (last_char !== undefined) {
				line.container.width = last_char.pre_width + last_char.width;
			} else {
				line.container.width = 0;
			}
			let rejust = true;
			let ___OBJECT_1 = this._edit.line_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let line_info = ___OBJECT_1[index - 1];
				if (line_info === undefined) break;
				if (line_info.container.width > line.container.width) {
					rejust = false;
					break;
				}
			}
			if (rejust) {
				this._edit.code_screen.container.width = line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
				this._edit.code_screen.AdjustScrollBar();
			}
			if (need_revoke) {
				let new_it_line = this._it_line;
				let new_it_char = this._it_char;
				let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteLeftRevoke, this._edit, this, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind === undefined);
				if (revoke_bind !== undefined) {
					revoke_bind.PushRevoke(revoke);
				} else {
					this._edit.revoke_list.PushRevoke(revoke);
				}
			}
			this._edit.UpdateLineFind(this._it_line);
			return true;
		}
		if (this._it_line <= 1) {
			return false;
		}
		let pre_line = this._edit.line_list[this._it_line - 1 - 1];
		if (pre_line === undefined) {
			return false;
		}
		let cur_line = this._edit.line_list[this._it_line - 1];
		if (cur_line === undefined) {
			return false;
		}
		let old_char_count = pre_line.char_count;
		let it_char = pre_line.char_count;
		let revoke_content = "";
		while (it_char > 0 && pre_line.char_list[it_char - 1].width <= 0) {
			revoke_content = pre_line.char_list[it_char - 1].char + revoke_content;
			pre_line.char_count = pre_line.char_count - (1);
			pre_line.char_list[it_char - 1] = undefined;
			it_char = it_char - (1);
		}
		let new_it_line = this._it_line - 1;
		let new_it_char = it_char;
		if (this._edit.language !== undefined) {
			this._edit.language.DeleteText(new_it_line, new_it_char, new_it_line, old_char_count - 1);
		}
		let pre_width = 0.0;
		if (pre_line.char_count > 0) {
			let last_char = pre_line.char_list[pre_line.char_count - 1];
			pre_width = last_char.pre_width + last_char.width;
		}
		for (let i = 1; i <= cur_line.char_count; i += 1) {
			let char = cur_line.char_list[i - 1];
			char.pre_width = pre_width;
			if (char.text !== undefined) {
				char.text.x = pre_width;
			}
			pre_line.container.AddChar(char);
			pre_width = pre_width + (char.width);
			pre_line.char_count = pre_line.char_count + (1);
			pre_line.char_list[pre_line.char_count - 1] = char;
		}
		pre_line.container.width = pre_width;
		this._edit.code_linear.RemoveChild(cur_line.container);
		this._edit.line_count = this._edit.line_count - (1);
		ALittle.List_Remove(this._edit.line_list, this._it_line);
		this.SetLineChar(new_it_line, new_it_char);
		if (this._edit.code_screen.container.width < pre_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH) {
			this._edit.code_screen.container.width = pre_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		}
		this._edit.code_screen.AdjustScrollBar();
		if (need_revoke) {
			let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteLeftRevoke, this._edit, this, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind === undefined);
			if (revoke_bind !== undefined) {
				revoke_bind.PushRevoke(revoke);
			} else {
				this._edit.revoke_list.PushRevoke(revoke);
			}
		}
		this._edit.UpdateLineFind(this._it_line);
		this._edit.UpdateLineNumber();
		return true;
	},
	DeleteRight : function(need_revoke, revoke_bind) {
		let old_it_line = this._it_line;
		let old_it_char = this._it_char;
		let line = this._edit.line_list[this._it_line - 1];
		if (line === undefined) {
			return false;
		}
		let count = line.char_count;
		while (count > 0 && line.char_list[count - 1].width <= 0) {
			-- count;
		}
		if (this._it_char < count) {
			if (this._edit.language !== undefined) {
				this._edit.language.DeleteText(this._it_line, this._it_char, this._it_line, this._it_char);
			}
			let char = line.char_list[this._it_char + 1 - 1];
			let revoke_content = char.char;
			if (char.text !== undefined) {
				line.container._text.RemoveChild(char.text);
			}
			line.char_count = line.char_count - (1);
			ALittle.List_Remove(line.char_list, this._it_char + 1);
			for (let i = this._it_char + 1; i <= line.char_count; i += 1) {
				line.char_list[i - 1].pre_width = line.char_list[i - 1].pre_width - (char.width);
				if (line.char_list[i - 1].text !== undefined) {
					line.char_list[i - 1].text.x = line.char_list[i - 1].text.x - (char.width);
				}
			}
			this.SetLineChar(this._it_line, this._it_char);
			let last_char = line.char_list[line.char_count - 1];
			if (last_char !== undefined) {
				line.container.width = last_char.pre_width + last_char.width;
			} else {
				line.container.width = 0;
			}
			let rejust = true;
			let ___OBJECT_2 = this._edit.line_list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let line_info = ___OBJECT_2[index - 1];
				if (line_info === undefined) break;
				if (line_info.container.width > line.container.width) {
					rejust = false;
					break;
				}
			}
			if (rejust) {
				this._edit.code_screen.container.width = line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
				this._edit.code_screen.AdjustScrollBar();
			}
			let new_it_line = this._it_line;
			let new_it_char = this._it_char;
			if (need_revoke) {
				let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteRightRevoke, this._edit, this, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind === undefined);
				if (revoke_bind !== undefined) {
					revoke_bind.PushRevoke(revoke);
				} else {
					this._edit.revoke_list.PushRevoke(revoke);
				}
			}
			this._edit.UpdateLineFind(this._it_line);
			return true;
		}
		if (this._it_line >= this._edit.line_count) {
			return false;
		}
		let cur_line = line;
		let next_line = this._edit.line_list[this._it_line + 1 - 1];
		if (next_line === undefined) {
			return false;
		}
		let old_char_count = cur_line.char_count;
		let it_char = cur_line.char_count;
		let revoke_content = "";
		while (it_char > 0 && (cur_line.char_list[it_char - 1].char === "\r" || cur_line.char_list[it_char - 1].char === "\n")) {
			revoke_content = cur_line.char_list[it_char - 1].char + revoke_content;
			cur_line.char_count = cur_line.char_count - (1);
			cur_line.char_list[it_char - 1] = undefined;
			it_char = it_char - (1);
		}
		let new_it_line = this._it_line;
		let new_it_char = it_char;
		if (this._edit.language !== undefined) {
			this._edit.language.DeleteText(this._it_line, it_char, this._it_line, old_char_count - 1);
		}
		let pre_width = 0.0;
		if (cur_line.char_count > 0) {
			let last_char = cur_line.char_list[cur_line.char_count - 1];
			pre_width = last_char.pre_width + last_char.width;
		}
		for (let i = 1; i <= next_line.char_count; i += 1) {
			let char = next_line.char_list[i - 1];
			char.pre_width = pre_width;
			if (char.text !== undefined) {
				char.text.x = pre_width;
			}
			cur_line.container.AddChar(char);
			pre_width = pre_width + (char.width);
			cur_line.char_count = cur_line.char_count + (1);
			cur_line.char_list[cur_line.char_count - 1] = char;
		}
		cur_line.container.width = pre_width;
		this._edit.code_linear.RemoveChild(next_line.container);
		this._edit.line_count = this._edit.line_count - (1);
		ALittle.List_Remove(this._edit.line_list, this._it_line + 1);
		this.SetLineChar(new_it_line, new_it_char);
		if (this._edit.code_screen.container.width < cur_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH) {
			this._edit.code_screen.container.width = cur_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH;
		}
		this._edit.code_screen.AdjustScrollBar();
		if (need_revoke) {
			let revoke = ALittle.NewObject(AUIPlugin.AUICodeDeleteRightRevoke, this._edit, this, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind === undefined);
			if (revoke_bind !== undefined) {
				revoke_bind.PushRevoke(revoke);
			} else {
				this._edit.revoke_list.PushRevoke(revoke);
			}
		}
		this._edit.UpdateLineFind(this._it_line);
		this._edit.UpdateLineNumber();
		return true;
	},
	Hide : function() {
		if (this._loop !== undefined) {
			this._loop.Stop();
			this._loop = undefined;
		}
		this.visible = false;
	},
	Update : function() {
		if (this.abs_visible) {
			this._flash_alpha = this._flash_alpha + this._flash_dir;
			if ((this._flash_dir < 0 && this._flash_alpha < -0.05) || (this._flash_dir > 0 && this._flash_alpha > 1.5)) {
				this._flash_dir = -this._flash_dir;
			}
			this.alpha = this._flash_alpha;
		}
	},
}, "AUIPlugin.AUICodeCursor");

}